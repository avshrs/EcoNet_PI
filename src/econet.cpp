#include "econet.h"
#include <iomanip>
#include <iostream>
#include <ctime>   // localtime
#include <stdlib.h>
#include <algorithm>
#include "Mosquitto.h"
#include <sstream> //for std::stringstream


void EcoNet::init(std::string serialName, int boudrate, int lead_zero)
{
        serial.serial_open(serialName.c_str(), boudrate, lead_zero);
}

void EcoNet::run()
{   
    std::vector<uint8_t> header;
    header.reserve(10);
    std::vector<uint8_t> payload;
    payload.reserve(1024);
    std::vector<uint8_t> message;
    message.reserve(1024);
    deb1.reserve(1024);
    deb2.reserve(1024);
    deb3.reserve(1024);

    for(int i =0; i<1024 ; i++)
    {
        deb1.push_back(0);
        deb2.push_back(0);
        deb3.push_back(0);
    }
    auto start = timer.now();
    while (true)
    {
        header.clear();
        payload.clear();
        message.clear();
        
        serial.serial_read_bytes(header, 8); 

        // print_buffer(header.data(), header.size());
        
        auto ecomax_header = *reinterpret_cast<Ecomax_920_Frame_Header*>(header.data());
       
        if(ecomax_header.frame_begine == frame_begin)
        {
            for(int i =0 ; i< ecomax_header.frame_size - 8; i++)
                serial.serial_read_byte(payload);

            message.insert(message.end(), header.begin(), header.end());
            message.insert(message.end(), payload.begin(), payload.end());
            
            
            if(crc(message) == static_cast<uint8_t>(message.at(message.size()-2)))
            {

                if(ecomax_header.src_address == ecomax_address 
                    && ecomax_header.payload_type == ecomax_live_data_frame)
                {
                    show_diff(payload);
                    ecomax920_payload = *reinterpret_cast<Ecomax_920_Live_Data_Frame_payload*>(payload.data());
                    // analyze_frame_ecomax_920P1(payload);
                    update_statuses();
                    
                }
                else if(ecomax_header.src_address == ecomax_address 
                    && ecomax_header.payload_type == ecomax_settings_frame)
                {   
                    //ecomax stored settings 
                   
                    analyze_frame_ecomax_920P1_settings(message);
                    //update_statuses();
                }
                else if(ecomax_header.src_address == econet_address) // debug
                {  
                    //econet frames used to get set addresses  
                }   
                else if(ecomax_header.src_address == ecoster_address
                    && ecomax_header.payload_type == ecoster_frame)
                {
                    //ecoster touch live frame 
                    analyze_frame_ecoster(payload);
                   // update_statuses();
                }            
                else if(ecomax_header.src_address == ecoster_address 
                    && ecomax_header.payload_type == ecoster_settings_frame)
                {
                    //ecoster touch stored settings
                    analyze_frame_ecoster_settings(message);
                   // update_statuses();
                } 
                else
                {
                    //  for debug 
                    //  print_buffer(message.data(), message.size());
                }

                auto deltaTime = std::chrono::duration_cast<mi>(timer.now() - start).count();
                if( deltaTime > 60e6)
                {   
                    // set the same value to force master broadcsat with all ecomax settings 
                    // only transmitted on change
                    uint8_t temp = std::stoi(get_huw_temp_target());

                    set_huw_temp(temp);
                    start = timer.now();
                }
                
            }
        }

    }
}

void EcoNet::print_buffer(uint8_t *buf, int len)
{   //debug tool
    std::cout << date()<< "Len: "<< std::dec <<len << "|";
    for(int i = 0; i < len  ; i++)
        {
        std::cout << " 0x" << std::setw(2);
        std::cout << std::setfill('0') << std::hex;
        std::cout << static_cast<int>(buf[i]);
        }
    std::cout <<" | " << std::endl;
}


void EcoNet::show_diff(std::vector<uint8_t> payload)
{   //debug tool
  
    for(int i = 0; i <  static_cast<int>(payload.size()) ; i++)
    {
        if(payload.at(i) != deb1.at(i) && i != 29 && i < 78 && i > 116)
        {
            std::cout << i << ": " ;
            std::cout << " 0x" << std::setw(2);
            std::cout << std::setfill('0') << std::hex;
            std::cout << static_cast<int>(payload.at(i));
            
            std::cout << " 0x" << std::setw(2);
            std::cout << std::setfill('0') << std::hex;
            std::cout << static_cast<int>(deb1.at(i));
            
            std::cout << " 0x" << std::setw(2);
            std::cout << std::setfill('0') << std::hex;
            std::cout << static_cast<int>(deb2.at(i));
            
            std::cout << " 0x" << std::setw(2);
            std::cout << std::setfill('0') << std::hex;
            std::cout << static_cast<int>(deb3.at(i));
            std::cout <<"\n";
            std::cout <<" | " << std::endl;
        }
       
    }
    deb3=deb2;
    deb2=deb1;
    deb1=payload;
    
}



std::string EcoNet::date()
{   //for debug 
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);      
    std::stringstream ss; 
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ") ;
    return ss.str();
}

uint8_t EcoNet::crc(std::vector<uint8_t> &message)
{   //crc for whole frame
    uint8_t tmp = message.at(0);
    for(int i = 1 ; i < static_cast<int>(message.size()-2) ; i++ )
    {
        tmp = tmp^message.at(i);
    }
    return tmp;
}
uint8_t EcoNet::crc_set(std::vector<uint8_t> &message)
{   // crc for frame only with data
    uint8_t tmp = message.at(0);
    for(int i = 1 ; i < static_cast<int>(message.size()) ; i++ )
    {
        tmp = tmp^message.at(i);
    }
    return tmp;
}

void EcoNet::analyze_frame_ecoster(std::vector<uint8_t> &payload)
{  
    ecoster_payload.home_temp = retrun_float(payload, 20); 
    ecoster_payload.home_temp_target = retrun_float(payload, 16); 
    ecoster_payload.ecoster_1_temp = retrun_float(payload, 24); 
    ecoster_payload.ecoster_2_temp = retrun_float(payload,28); 
}

void EcoNet::analyze_frame_econet(std::vector<uint8_t> &payload)
{
    if(payload.at(0))
    {
        // only for complicator 
        // not needed to get any data from econet device
    }
    
}
void EcoNet::analyze_frame_ecoster_settings(std::vector<uint8_t> &payload)
{
     std::string value;
     value = std::to_string(static_cast<int>(payload.at(44)));
     value += ".";
     value += std::to_string(static_cast<int>(payload.at(47)));
     econet_set_values.pub_room_thermostat_day_temp = value;

     value = std::to_string(static_cast<int>(payload.at(41)));
     econet_set_values.pub_room_thermostat_hysteresis = value;
     
     value = std::to_string(static_cast<int>(payload.at(50)));
     value += ".";
     value += std::to_string(static_cast<int>(payload.at(53)));
     econet_set_values.pub_room_thermostat_night_temp = value;
     if(payload.at(11) == 0x00)
        value = "auto";  
     else if(payload.at(11) == 0x02)
        value = "heat";
     else if(payload.at(11) == 0x03)
        value = "off";        
    //  else
    //     value = "value error";
    //  if(payload.at(11) == 0x00)
    //     value = "Schedule";  
    //  else if(payload.at(11) == 0x01)
    //     value = "Economy";
    //  else if(payload.at(11) == 0x02)
    //     value = "Comfort";
    //  else if(payload.at(11) == 0x03)
    //     value = "Outside";        
    //  else
    //     value = "value error";
     econet_set_values.pub_room_thermostat_operating_mode = value;
}
void EcoNet::analyze_frame_ecomax_920P1_settings(std::vector<uint8_t> &payload)
{
     std::string value;
     value = std::to_string(static_cast<int>(payload.at(175)));
     econet_set_values.pub_huw_temp = value;

     if(payload.at(184) == 0x01)
        value = "heat";
     else if(payload.at(184) == 0x00)
        value = "Off";        

    // if(payload.at(184) == 0x01)
    //     value = "Priority";
    //  else if(payload.at(184) == 0x02)
    //     value = "Po Priority";
    //  else if(payload.at(184) == 0x00)
    //     value = "Off";        
    //  else
    //     value = "value error";  


     econet_set_values.pub_huw_pump_mode = value;

     float tmp = (static_cast<int>(payload.at(187)))/10;
     value = std::to_string(tmp);
     econet_set_values.pub_huw_temp_hysteresis = value;
     
     value = std::to_string(static_cast<int>(payload.at(190)));
     econet_set_values.pub_huw_container_disinfection = value;
     
     value = std::to_string(static_cast<int>(payload.at(166)));
     econet_set_values.pub_boiler_temp = value;
     
     value = std::to_string(static_cast<int>(payload.at(10)));
     econet_set_values.pub_boiler_max_power_kw = value;
     
     value = std::to_string(static_cast<int>(payload.at(13)));
     econet_set_values.pub_boiler_mid_power_kw = value;
     
     value = std::to_string(static_cast<int>(payload.at(16)));
     econet_set_values.pub_boiler_min_power_kw = value;
     
     value = std::to_string(static_cast<int>(payload.at(19)));
     econet_set_values.pub_boiler_max_power_fan = value;
     
     value = std::to_string(static_cast<int>(payload.at(22)));
     econet_set_values.pub_boiler_mid_power_fan = value;

     value = std::to_string(static_cast<int>(payload.at(25)));
     econet_set_values.pub_boiler_min_power_fan = value;

     value = std::to_string(static_cast<int>(payload.at(226)));
     econet_set_values.pub_mixer_temp = value;
     
     if(payload.at(196) == 0x01)
        value = "heat";
     else if(payload.at(196) == 0x02)
        value = "off";
     else if(payload.at(196) == 0x00)
        value = "auto";        
    //  else
    //     value = "Value error";
    //  if(payload.at(196) == 0x01)
    //     value = "Winter";
    //  else if(payload.at(196) == 0x02)
    //     value = "Summer";
    //  else if(payload.at(196) == 0x00)
    //     value = "Auto";        
    //  else
    //     value = "Value error";
     econet_set_values.pub_room_thermostat_summer_winter_mode = value;
}
// void EcoNet::analyze_frame_ecomax_920P1(std::vector<uint8_t> &payload)
// {   
//     ecomax920_payload.operating_status = payload.at(29); 
//     ecomax920_payload.huw_temp = retrun_float(payload, 78);      
//     ecomax920_payload.mixer_temp = retrun_float(payload, 82);                                             
//     ecomax920_payload.weather_temp = retrun_float(payload, 86);  
//     ecomax920_payload.boiler_return_temp = retrun_float(payload, 90);   
//     ecomax920_payload.exhaust_temp = retrun_float(payload, 94); 
//     ecomax920_payload.feeder_temp = retrun_float(payload, 98);   
//     ecomax920_payload.boiler_temp = retrun_float(payload, 102);      
//     ecomax920_payload.flame_sensor = retrun_float(payload, 106);                                                   
//     ecomax920_payload.upper_buffer_temp = retrun_float(payload, 110); 
//     ecomax920_payload.lower_buffer_temp = retrun_float(payload, 114); 
//     ecomax920_payload.huw_temp_target = static_cast<int>(payload.at(167)); 
//     ecomax920_payload.mixer_temp_target =  static_cast<int>(payload.at(166));
//     ecomax920_payload.boiler_temp_target = static_cast<int>(payload.at(172));
//     ecomax920_payload.huw_pomp_state = static_cast<int>(payload.at(194));
//     ecomax920_payload.fuel_level = static_cast<int>(payload.at(217));
//     ecomax920_payload.fan_in_power = static_cast<int>(payload.at(254));
//     ecomax920_payload.fan_out_power = static_cast<int>(payload.at(255));
//     ecomax920_payload.boiler_power_kw = retrun_float(payload, 256);
//     ecomax920_payload.fuel_stream = retrun_float(payload, 260);
//     ecomax920_payload.boiler_pomp_state = static_cast<int>(payload.at(265));
//     ecomax920_payload.power_max_time = retrun_short(payload, 266); 
//     ecomax920_payload.power_medium_time = retrun_short(payload, 268);
//     ecomax920_payload.power_min_time = retrun_short(payload, 270);
//     ecomax920_payload.feeder_time = retrun_short(payload, 272);
//     ecomax920_payload.ignitions = retrun_short(payload, 274);
//     ecomax920_payload.ignitions_fails = retrun_short(payload, 276);
// }

// void EcoNet::analyze_frame_ecomax_920P1(std::vector<uint8_t> &payload)
// {   

// }

float EcoNet::retrun_float(std::vector<uint8_t> &payload, int p)
{
    union {
        float f;
        uint32_t ui;
    } u;
    u.ui = (payload.at(p)) | (payload.at(p+1) << 8) | 
           (payload.at(p+2) << 16) | (payload.at(p+3) << 24);
    
    return u.f;
}

short EcoNet::retrun_short(std::vector<uint8_t> &payload, int p)
{
    union {
        short sh;
        uint16_t ui;
    } u;
    u.ui = ((payload.at(p)) | (payload.at(p+1) << 8)) ;
           
    return u.sh;
}

std::string EcoNet::get_operating_status()
{
    return operating_status_sting.at(ecomax920_payload.operating_status);
}
std::string EcoNet::get_huw_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.huw_temp;
    return out.str();
}
std::string EcoNet::get_feeder_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.feeder_temp;
    return out.str();
}
std::string EcoNet::get_boiler_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.boiler_temp;
    return out.str();    
}
std::string EcoNet::get_weather_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.weather_temp;
    return out.str();   
}
std::string EcoNet::get_exhaust_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.exhaust_temp;
    return out.str();   
}
std::string EcoNet::get_mixer_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.boiler_temp;
    return out.str();   
    return std::to_string(ecomax920_payload.mixer_temp);   
}
std::string EcoNet::get_boiler_return_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.boiler_return_temp;
    return out.str();   
}
std::string EcoNet::get_upper_buffer_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.upper_buffer_temp;
    return out.str();   
}
std::string EcoNet::get_lower_buffer_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.lower_buffer_temp;
    return out.str();   
}
std::string EcoNet::get_flame_sensor()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.flame_sensor;
    return out.str();   
}
std::string  EcoNet::get_huw_temp_target()
{
    return std::to_string(ecomax920_payload.huw_temp_target);
}
std::string  EcoNet::get_boiler_temp_target()
{
    return std::to_string(ecomax920_payload.boiler_temp_target);
}
std::string  EcoNet::get_mixer_temp_target()
{
    return std::to_string(ecomax920_payload.mixer_temp_target);
}
std::string  EcoNet::get_fuel_level()
{
    return std::to_string(ecomax920_payload.fuel_level);
}
std::string  EcoNet::get_fan_out_power()
{
    return std::to_string(ecomax920_payload.fan_out_power);
}
std::string  EcoNet::get_fan_in_power()
{
    return std::to_string(ecomax920_payload.fan_in_power);
}
std::string EcoNet::get_fuel_stream()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.fuel_stream;
    return out.str();   
}
std::string EcoNet::get_boiler_power_kw()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecomax920_payload.boiler_power_kw;
    return out.str();   
}
std::string EcoNet::get_power_max_time()
{
    return std::to_string(ecomax920_payload.power_max_time);
}
std::string EcoNet::get_power_medium_time()
{
    return std::to_string(ecomax920_payload.power_medium_time);
}
std::string EcoNet::get_power_min_time()
{
    return std::to_string(ecomax920_payload.power_min_time);
}
std::string EcoNet::get_feeder_time()
{
    return std::to_string(ecomax920_payload.feeder_time);
}
std::string EcoNet::get_ignitions()
{
    return std::to_string(ecomax920_payload.ignitions);
}
std::string EcoNet::get_ignitions_fails()
{
    return std::to_string(ecomax920_payload.ignitions_fails);
}
std::string EcoNet::get_ecoster_home_temp()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecoster_payload.home_temp;
    return out.str();   
}
std::string EcoNet::get_ecoster_home_temp_target()
{
    std::stringstream out;
    out << std::fixed << std::setprecision(2) << ecoster_payload.home_temp_target;
    return out.str();   
} 
std::string EcoNet::get_huw_pomp_state()
{
    return std::to_string(ecomax920_payload.huw_pomp_state);
} 
std::string EcoNet::get_boiler_pomp_state()
{
    return std::to_string(ecomax920_payload.boiler_pomp_state);
} 


void EcoNet::set_huw_temp(uint8_t temp)
{
    if(temp <= 70 && temp >=20)
    {
        std::vector<uint8_t> buf = {0x68, 0x10, 0x00, 0x45, 0x56, 0x30, 0x05, 0x57, 0x01, 0x00, 0x04, 0x01 ,0x05};
        buf.push_back(temp);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_huw_temp out of range 20 - 70" <<std::endl;
    }
}
void EcoNet::set_huw_pump_mode(std::string pump_mode)
{
    if(pump_mode == "heat")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x39, 0x01};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else if(pump_mode == "no_priority")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x39, 0x02};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else if(pump_mode == "off")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x39, 0x00};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }    
    else
    {
        std::cout<< date() << "<set_huw_pump_mode out of range: priority | no_priority | off" <<std::endl;
    }
}

void EcoNet::set_huw_temp_hysteresis(uint8_t hysteresis)
{
    if(hysteresis <= 30 && hysteresis >= 1)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3a};
        buf.push_back(hysteresis);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_huw_temp_hysteresis hysteresis out of range 1 - 30" <<std::endl;
    }
}
void EcoNet::set_huw_container_disinfection(bool state)
{
    if(state)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3b, 0x01};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3b, 0x00};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);    
    }
}

void EcoNet::set_room_thermostat_summer_winter_mode(std::string state)
{
    if(state == "heat")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3d, 0x00};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else if (state == "off")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3d, 0x01};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);    
    }
    else if (state == "auto")
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x3d, 0x02};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);    
    }
    else
    {
        std::cout<< date() << "set_room_thermostat_summer_winter_mode winter | summer | auto" <<std::endl;
    }
}

void EcoNet::set_boiler_temp(uint8_t temp)
{
    if(temp <= 80 && temp >=35)
    {
        std::vector<uint8_t> buf = {0x68, 0x10, 0x00, 0x45, 0x56, 0x30, 0x05, 0x57, 0x01, 0x00, 0x04, 0x00, 0x05};
        buf.push_back(temp);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_temp out of range 35 - 80" <<std::endl;
    }
}

void EcoNet::set_boiler_on_off(bool state)
{
    if(state)
    {
        std::vector<uint8_t> buf = {0x68, 0x0b, 0x00, 0x45, 0x56, 0x30, 0x05, 0x3b, 0x01 };
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::vector<uint8_t> buf = {0x68, 0x0b, 0x00, 0x45, 0x56, 0x30, 0x05, 0x3b, 0x00 };
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);    }
}

void EcoNet::set_mixer_temp(uint8_t temp)
{
    if(temp <= 70 && temp >=20)
    {
        std::vector<uint8_t> buf = {0x68, 0x10, 0x00, 0x45, 0x56, 0x30, 0x05, 0x57, 0x01, 0x00, 0x04, 0x07, 0x05};
        buf.push_back(temp);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_mixer_temp out of range 20 - 70" <<std::endl;
    }
}


void EcoNet::set_room_thermostat_night_temp(float temp_)
{
    
    if(temp_ <= 35 && temp_ >=10)
    {
        short temp = temp_*10;
        
        uint8_t uin[2] = {0};
        
        uin[0] = static_cast<uint8_t>(temp);
        uin[1] = static_cast<uint8_t>(temp >> 8);

        std::vector<uint8_t> buf = {0x68, 0x0d, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d,  0x0b};
        buf.push_back(uin[0]);
        buf.push_back(uin[1]);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_room_thermostat_night_temp temp out of range 10 - 35" <<std::endl;
    }
}

void EcoNet::set_room_thermostat_day_temp(float temp_)
{
    if(temp_ <= 35 && temp_ >=10)
    {
        short temp = temp_*10;
        
        uint8_t uin[2] = {0};
        
        uin[0] = static_cast<uint8_t>(temp);
        uin[1] = static_cast<uint8_t>(temp >> 8);

        std::vector<uint8_t> buf = {0x68, 0x0d, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d,  0x0a};
        buf.push_back(uin[0]);
        buf.push_back(uin[1]);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_room_thermostat_day_temp temp out of range 10 - 35" <<std::endl;
    }
}


void EcoNet::set_room_thermostat_operating_mode(std::string state)
{
    if(state == "heat")
    {
        std::vector<uint8_t> buf = {0x68, 0x0c, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d, 0x01, 0x02};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else if (state == "economy")
    {
        std::vector<uint8_t> buf = {0x68, 0x0c, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d, 0x01, 0x01};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf); 
    }
    else if (state == "auto")
    {
        std::vector<uint8_t> buf = {0x68, 0x0c, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d, 0x01, 0x00};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf); 
    }
    else if (state == "off")
    {
        std::vector<uint8_t> buf = {0x68, 0x0c, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d, 0x01, 0x03};
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf); 
    }
    else
    {
        std::cout<< date() << "set_room_thermostat_operating_mode temp out of range comfort | economy | schedule | outside " <<std::endl;
    }
}
void EcoNet::set_room_thermostat_hysteresis(float hysteresis)
{

    if(hysteresis <= 5 ) //0x05 0.5C //0x15 1.5C
    {
        std::vector<uint8_t> buf = {0x68, 0x0c, 0x00, 0x45, 0x56, 0x30, 0x05, 0x5d, 0x09};
        buf.push_back(static_cast<uint8_t>(hysteresis*10));
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_room_thermostat_hysteresis out of range 0 - 5" <<std::endl;
    }
}

void EcoNet::set_boiler_max_power_kw(uint8_t power_kw)
{
    if(power_kw <= 18 && power_kw >=9)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x00};
        buf.push_back(power_kw);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_max_power_kw out of range 9 - 18" <<std::endl;
    }
}

void EcoNet::set_boiler_mid_power_kw(uint8_t power_kw)
{
    if(power_kw <= 18 && power_kw >=9)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x01};
        buf.push_back(power_kw);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_mid_power_kw out of range 9 - 18" <<std::endl;
    }
}
void EcoNet::set_boiler_min_power_kw(uint8_t power_kw)
{
    if(power_kw <= 6 && power_kw >=2)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x02};
        buf.push_back(power_kw);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_min_power_kw out of range 2 - 6" <<std::endl;
    }
}
void EcoNet::set_boiler_max_power_fan(uint8_t fun_max)
{
    if(fun_max <= 60 && fun_max >=28)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x03};
        buf.push_back(fun_max);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_max_power_fan out of range 28 - 60" <<std::endl;
    }
}

void EcoNet::set_boiler_mid_power_fan(uint8_t fun_mid)
{
    if(fun_mid <= 30 && fun_mid >=25)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x04};
        buf.push_back(fun_mid);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_mid_power_fan out of range 25 - 30" <<std::endl;
    }
}
void EcoNet::set_boiler_min_power_fan(uint8_t fun_min)
{
    if(fun_min <= 25 && fun_min >=17)
    {
        std::vector<uint8_t> buf = {0x68, 0x0e, 0x00, 0x45, 0x56, 0x30, 0x05, 0x56, 0x05, 0x01, 0x05};
        buf.push_back(fun_min);
        buf.push_back(crc_set(buf));
        buf.push_back(0x16);
        serial.serial_send(buf);
    }
    else
    {
        std::cout<< date() << "set_boiler_min_power_fan out of range 17 - 25" <<std::endl;
    }
}


std::string EcoNet::get_huw_pump_mode()
{
    return econet_set_values.pub_huw_pump_mode;
}
std::string EcoNet::get_huw_temp_hysteresis()
{
    return econet_set_values.pub_huw_temp_hysteresis ;
}
std::string EcoNet::get_huw_container_disinfection()
{
    return econet_set_values.pub_huw_container_disinfection;
}
std::string EcoNet::get_boiler_on_off()
{
    return econet_set_values.pub_boiler_on_off;
}
std::string EcoNet::get_boiler_max_power_kw()
{
    return econet_set_values.pub_boiler_max_power_kw;
}
std::string EcoNet::get_boiler_mid_power_kw()
{
    return econet_set_values.pub_boiler_mid_power_kw;
}
std::string EcoNet::get_boiler_min_power_kw()
{
    return econet_set_values.pub_boiler_min_power_kw;
}
std::string EcoNet::get_boiler_max_power_fan()
{
    return econet_set_values.pub_boiler_max_power_fan;
}
std::string EcoNet::get_boiler_mid_power_fan()
{
    return econet_set_values.pub_boiler_mid_power_fan;
}
std::string EcoNet::get_boiler_min_power_fan()
{
    return econet_set_values.pub_boiler_min_power_fan;
}

std::string EcoNet::get_room_thermostat_summer_winter_mode()
{    
    return econet_set_values.pub_room_thermostat_summer_winter_mode;
}
std::string EcoNet::get_room_thermostat_night_temp()
{
    return econet_set_values.pub_room_thermostat_night_temp;
}
std::string EcoNet::get_room_thermostat_day_temp()
{
    return econet_set_values.pub_room_thermostat_day_temp;
}
std::string EcoNet::get_room_thermostat_operating_mode()
{
    return econet_set_values.pub_room_thermostat_operating_mode;
}
std::string EcoNet::get_room_thermostat_hysteresis()
{
    return econet_set_values.pub_room_thermostat_hysteresis;
}
void EcoNet::register_mqtt(Mqtt_Client *mqtt_)
{
    mqtt = mqtt_;
}
void EcoNet::register_cfg(Config_manager *cfg_)
{
    cfg = cfg_;
}










void EcoNet::update_statuses()
{
    if (ecomax920_buffer.huw_temp != ecomax920_payload.huw_temp)
    {
         mqtt->pub_state(get_huw_temp(), cfg->sub_get_huw_temp());
        ecomax920_buffer.huw_temp = ecomax920_payload.huw_temp;
    }
    if (ecomax920_buffer.operating_status != ecomax920_payload.operating_status)
    {
         mqtt->pub_state(get_operating_status(), cfg->sub_get_operating_status());
        ecomax920_buffer.operating_status = ecomax920_payload.operating_status;
    }

    if (ecomax920_buffer.feeder_temp != ecomax920_payload.feeder_temp)
    {
         mqtt->pub_state(get_feeder_temp(), cfg->sub_get_feeder_temp());
        ecomax920_buffer.feeder_temp = ecomax920_payload.feeder_temp;
    }
  
    if (ecomax920_buffer.boiler_temp != ecomax920_payload.boiler_temp)
    {
         mqtt->pub_state(get_boiler_temp(), cfg->sub_get_boiler_temp());
        ecomax920_buffer.boiler_temp = ecomax920_payload.boiler_temp;
    }

    if (ecomax920_buffer.boiler_return_temp != ecomax920_payload.boiler_return_temp)
    {
         mqtt->pub_state(get_boiler_return_temp(), cfg->sub_get_boiler_return_temp());
        ecomax920_buffer.boiler_return_temp = ecomax920_payload.boiler_return_temp;
    }

    if (ecomax920_buffer.flame_sensor != ecomax920_payload.flame_sensor)
    {
         mqtt->pub_state(get_flame_sensor(), cfg->sub_get_flame_sensor());
        ecomax920_buffer.flame_sensor = ecomax920_payload.flame_sensor;
    }

    if (ecomax920_buffer.upper_buffer_temp != ecomax920_payload.upper_buffer_temp)
    {
         mqtt->pub_state(get_upper_buffer_temp(), cfg->sub_get_upper_buffer_temp());
        ecomax920_buffer.upper_buffer_temp = ecomax920_payload.upper_buffer_temp;
    }

    if (ecomax920_buffer.lower_buffer_temp != ecomax920_payload.lower_buffer_temp)
    {
         mqtt->pub_state(get_lower_buffer_temp(), cfg->sub_get_lower_buffer_temp());
        ecomax920_buffer.lower_buffer_temp = ecomax920_payload.lower_buffer_temp;
    }

    if (ecomax920_buffer.weather_temp != ecomax920_payload.weather_temp)
    {
         mqtt->pub_state(get_weather_temp(), cfg->sub_get_weather_temp());
        ecomax920_buffer.weather_temp = ecomax920_payload.weather_temp;
    }

    if (ecomax920_buffer.exhaust_temp != ecomax920_payload.exhaust_temp)
    {
         mqtt->pub_state(get_exhaust_temp(), cfg->sub_get_exhaust_temp());
        ecomax920_buffer.exhaust_temp = ecomax920_payload.exhaust_temp;
    }

    if (ecomax920_buffer.mixer_temp != ecomax920_payload.mixer_temp)
    {
         mqtt->pub_state(get_mixer_temp(), cfg->sub_get_mixer_temp());
        ecomax920_buffer.mixer_temp = ecomax920_payload.mixer_temp;
    }

    if (ecomax920_buffer.boiler_power_kw != ecomax920_payload.boiler_power_kw)
    {
         mqtt->pub_state(get_boiler_power_kw(), cfg->sub_get_boiler_power_kw());
        ecomax920_buffer.boiler_power_kw = ecomax920_payload.boiler_power_kw;
    }

    if (ecomax920_buffer.fuel_stream != ecomax920_payload.fuel_stream)
    {
         mqtt->pub_state(get_fuel_stream(), cfg->sub_get_fuel_stream());
        ecomax920_buffer.fuel_stream = ecomax920_payload.fuel_stream;
    }

    if (ecomax920_buffer.huw_temp_target != ecomax920_payload.huw_temp_target)
    {
         mqtt->pub_state(get_huw_temp_target(), cfg->sub_get_huw_temp_target());
        ecomax920_buffer.huw_temp_target = ecomax920_payload.huw_temp_target;
    }

    if (ecomax920_buffer.boiler_temp_target != ecomax920_payload.boiler_temp_target)
    {
         mqtt->pub_state(get_boiler_temp_target(), cfg->sub_get_boiler_temp_target());
        ecomax920_buffer.boiler_temp_target = ecomax920_payload.boiler_temp_target;
    }

    if (ecomax920_buffer.mixer_temp_target != ecomax920_payload.mixer_temp_target)
    {
         mqtt->pub_state(get_mixer_temp_target(), cfg->sub_get_mixer_temp_target());
        ecomax920_buffer.mixer_temp_target = ecomax920_payload.mixer_temp_target;
    }

    if (ecomax920_buffer.fuel_level != ecomax920_payload.fuel_level)
    {
         mqtt->pub_state(get_fuel_level(), cfg->sub_get_fuel_level());
        ecomax920_buffer.fuel_level = ecomax920_payload.fuel_level;
    }

    if (ecomax920_buffer.fan_in_power != ecomax920_payload.fan_in_power)
    {
         mqtt->pub_state(get_fan_in_power(), cfg->sub_get_fan_in_power());
        ecomax920_buffer.fan_in_power = ecomax920_payload.fan_in_power;
    }

    if (ecomax920_buffer.fan_out_power != ecomax920_payload.fan_out_power)
    {
         mqtt->pub_state(get_fan_out_power(), cfg->sub_get_fan_out_power());
        ecomax920_buffer.fan_out_power = ecomax920_payload.fan_out_power;
    }

    if (ecomax920_buffer.boiler_power != ecomax920_payload.boiler_power_kw)
    {
         mqtt->pub_state(get_boiler_power_kw(), cfg->sub_get_boiler_power_kw());
        ecomax920_buffer.boiler_power = ecomax920_payload.boiler_power_kw;
    }

    if (ecomax920_buffer.huw_pomp_state != ecomax920_payload.huw_pomp_state)
    {
         mqtt->pub_state(get_huw_pomp_state(), cfg->sub_get_huw_pomp_state());
        ecomax920_buffer.huw_pomp_state = ecomax920_payload.huw_pomp_state;
    }

    if (ecomax920_buffer.boiler_pomp_state != ecomax920_payload.boiler_pomp_state)
    {
         mqtt->pub_state(get_boiler_pomp_state(), cfg->sub_get_boiler_pomp_state());
        ecomax920_buffer.boiler_pomp_state = ecomax920_payload.boiler_pomp_state;
    }
    
    if (ecomax920_buffer.power_max_time != ecomax920_payload.power_max_time)
    {
         mqtt->pub_state(get_power_max_time(), cfg->sub_get_power_max_time());
        ecomax920_buffer.power_max_time = ecomax920_payload.power_max_time;
    }

    if (ecomax920_buffer.power_medium_time != ecomax920_payload.power_medium_time)
    {
         mqtt->pub_state(get_power_medium_time(), cfg->sub_get_power_medium_time());
        ecomax920_buffer.power_medium_time = ecomax920_payload.power_medium_time;
    }

    if (ecomax920_buffer.power_min_time != ecomax920_payload.power_min_time)
    {
         mqtt->pub_state(get_power_min_time(), cfg->sub_get_power_min_time());
        ecomax920_buffer.power_min_time = ecomax920_payload.power_min_time;
    }

    if (ecomax920_buffer.feeder_time != ecomax920_payload.feeder_time)
    {
         mqtt->pub_state(get_feeder_time(), cfg->sub_get_feeder_time());
        ecomax920_buffer.feeder_time = ecomax920_payload.feeder_time;
    }

    if (ecomax920_buffer.ignitions != ecomax920_payload.ignitions)
    {
         mqtt->pub_state(get_ignitions(), cfg->sub_get_ignitions());
        ecomax920_buffer.ignitions = ecomax920_payload.ignitions;
    }

    if (ecomax920_buffer.ignitions_fails != ecomax920_payload.ignitions_fails)
    {
         mqtt->pub_state(get_ignitions_fails(), cfg->sub_get_ignitions_fails());
        ecomax920_buffer.ignitions_fails = ecomax920_payload.ignitions_fails;
    }

    if (ecoster_buffer.home_temp_target != ecoster_payload.home_temp_target)
    {
         mqtt->pub_state(get_ecoster_home_temp_target(), cfg->sub_get_ecoster_home_temp_target());
        ecoster_buffer.home_temp_target = ecoster_payload.home_temp_target;
    }

    if (ecoster_buffer.home_temp != ecoster_payload.home_temp)
    {
         mqtt->pub_state(get_ecoster_home_temp(), cfg->sub_get_ecoster_home_temp());
        ecoster_buffer.home_temp = ecoster_payload.home_temp;
    }

    if (econet_set_values.sub_get_huw_pump_mode != econet_set_values.sub_get_huw_pump_mode)
    {
         mqtt->pub_state(get_huw_pump_mode(), cfg->sub_get_huw_pump_mode());
        econet_set_values.sub_get_huw_pump_mode = econet_set_buffer.sub_get_huw_pump_mode;
    }    
       
    if (econet_set_values.sub_get_huw_temp_hysteresis != econet_set_values.sub_get_huw_temp_hysteresis)
    {
         mqtt->pub_state(get_huw_temp_hysteresis(), cfg->sub_get_huw_temp_hysteresis());
        econet_set_values.sub_get_huw_temp_hysteresis = econet_set_buffer.sub_get_huw_temp_hysteresis;
    }    

    if (econet_set_values.sub_get_huw_container_disinfection != econet_set_values.sub_get_huw_container_disinfection)
    {
         mqtt->pub_state(get_huw_container_disinfection(), cfg->sub_get_huw_container_disinfection());
        econet_set_values.sub_get_huw_container_disinfection = econet_set_buffer.sub_get_huw_container_disinfection;
    }    

    if (econet_set_values.sub_get_boiler_on_off != econet_set_values.sub_get_boiler_on_off)
    {
         mqtt->pub_state(get_boiler_on_off(), cfg->sub_get_boiler_on_off());
        econet_set_values.sub_get_boiler_on_off = econet_set_buffer.sub_get_boiler_on_off;
    }    

    if (econet_set_values.sub_get_boiler_max_power_kw != econet_set_values.sub_get_boiler_max_power_kw)
    {
         mqtt->pub_state(get_boiler_max_power_kw(), cfg->sub_get_boiler_max_power_kw());
        econet_set_values.sub_get_boiler_max_power_kw = econet_set_buffer.sub_get_boiler_max_power_kw;
    }    

    if (econet_set_values.sub_get_boiler_mid_power_kw != econet_set_values.sub_get_boiler_mid_power_kw)
    {
         mqtt->pub_state(get_boiler_mid_power_kw(), cfg->sub_get_boiler_mid_power_kw());
        econet_set_values.sub_get_boiler_mid_power_kw = econet_set_buffer.sub_get_boiler_mid_power_kw;
    }    

    if (econet_set_values.sub_get_boiler_min_power_kw != econet_set_values.sub_get_boiler_min_power_kw)
    {
         mqtt->pub_state(get_boiler_min_power_kw(), cfg->sub_get_boiler_min_power_kw());
        econet_set_values.sub_get_boiler_min_power_kw = econet_set_buffer.sub_get_boiler_min_power_kw;
    }    

    if (econet_set_values.sub_get_boiler_max_power_fan != econet_set_values.sub_get_boiler_max_power_fan)
    {
         mqtt->pub_state(get_boiler_max_power_fan(), cfg->sub_get_boiler_max_power_fan());
        econet_set_values.sub_get_boiler_max_power_fan = econet_set_buffer.sub_get_boiler_max_power_fan;
    }    

    if (econet_set_values.sub_get_boiler_mid_power_fan != econet_set_values.sub_get_boiler_mid_power_fan)
    {
         mqtt->pub_state(get_boiler_mid_power_fan(), cfg->sub_get_boiler_mid_power_fan());
        econet_set_values.sub_get_boiler_mid_power_fan = econet_set_buffer.sub_get_boiler_mid_power_fan;
    }    

    if (econet_set_values.sub_get_boiler_min_power_fan != econet_set_values.sub_get_boiler_min_power_fan)
    {
         mqtt->pub_state(get_boiler_min_power_fan(), cfg->sub_get_boiler_min_power_fan());
        econet_set_values.sub_get_boiler_min_power_fan = econet_set_buffer.sub_get_boiler_min_power_fan;
    }    

    if (econet_set_values.sub_get_room_thermostat_summer_winter_mode != econet_set_values.sub_get_room_thermostat_summer_winter_mode)
    {
         mqtt->pub_state(get_room_thermostat_summer_winter_mode(), cfg->sub_get_room_thermostat_summer_winter_mode());
        econet_set_values.sub_get_room_thermostat_summer_winter_mode = econet_set_buffer.sub_get_room_thermostat_summer_winter_mode;
    }    

    if (econet_set_values.sub_get_room_thermostat_night_temp != econet_set_values.sub_get_room_thermostat_night_temp)
    {
         mqtt->pub_state(get_room_thermostat_night_temp(), cfg->sub_get_room_thermostat_night_temp());
        econet_set_values.sub_get_room_thermostat_night_temp = econet_set_buffer.sub_get_room_thermostat_night_temp;
    }    

    if (econet_set_values.sub_get_room_thermostat_day_temp != econet_set_values.sub_get_room_thermostat_day_temp)
    {
         mqtt->pub_state(get_room_thermostat_day_temp(), cfg->sub_get_room_thermostat_day_temp());
        econet_set_values.sub_get_room_thermostat_day_temp = econet_set_buffer.sub_get_room_thermostat_day_temp;
    }    

    if (econet_set_values.sub_get_room_thermostat_operating_mode != econet_set_values.sub_get_room_thermostat_operating_mode)
    {
         mqtt->pub_state(get_room_thermostat_operating_mode(), cfg->sub_get_room_thermostat_operating_mode());
        econet_set_values.sub_get_room_thermostat_operating_mode = econet_set_buffer.sub_get_room_thermostat_operating_mode;
    }
       
    if (econet_set_values.sub_get_room_thermostat_hysteresis != econet_set_values.sub_get_room_thermostat_hysteresis)
    {
         mqtt->pub_state(get_room_thermostat_hysteresis(), cfg->sub_get_room_thermostat_hysteresis());
        econet_set_values.sub_get_room_thermostat_hysteresis = econet_set_buffer.sub_get_room_thermostat_hysteresis;
    }    
}