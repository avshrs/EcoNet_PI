#include "econet.h"
#include <iomanip>
#include <iostream>
#include <ctime>   // localtime
#include <stdlib.h>
#include <algorithm>


void EcoNet::init(std::string serialName, int boudrate, int lead_zero)
{
        serial.serial_open(serialName.c_str(), boudrate, lead_zero);
}

void EcoNet::run()
{   
    std::vector<uint8_t> header;
    header.reserve(10);
    std::vector<uint8_t> payload;
    payload.reserve(400);
    std::vector<uint8_t> message;
    payload.reserve(400);
    while (true)
    {
        header.clear();
        payload.clear();
        message.clear();

        serial.serial_read_bytes(header, 8); 
        if(header.at(0)==frame_begin)
        {
            short paylod_len = ((header.at(1)) | (header.at(2)<<8));
            for(int i =0 ; i< paylod_len - 8; i++)
                serial.serial_read_byte(payload);

            message.insert(message.end(), header.begin(), header.end());
            message.insert(message.end(), payload.begin(), payload.end());
            
            if(crc(message) == static_cast<uint8_t>(message.at(message.size()-2)))
            {
                // print_buffer(message.data(), message.size());

                if(header.at(4)==eco____address )
                {
                   print_buffer(message.data(), message.size());
                    // analyze_frame_ecomax_920P1(payload);
                }
            
                // if(header.at(4)==ecomax_address && header.at(7)==ecomax_frame)
                else if(header.at(4)==ecomax_address )
                {
                   //print_buffer(message.data(), message.size());
                    // analyze_frame_ecomax_920P1(payload);
                }
                // else if(header.at(4)==econet_address && header.at(7)==econet_frame)
                else if(header.at(4)==econet_address)
                {   
                //    std::cout <<date() << "econet: " ;
                //    print_buffer(message.data(), message.size() );
                }               
                // else if(header.at(4)==ecoster_address && header.at(7)==ecoster_frame)
                else if(header.at(4)==ecoster_address )
                {
                   // print_buffer(message.data(), message.size());
                    // analyze_frame_ecoster(payload);
                } 
                else
                {
                    print_buffer(message.data(), message.size());
                }
            }
        }
       

    }
}

void EcoNet::print_buffer(uint8_t *buf, int len)
{   
    std::cout << date()<< "Len: "<< std::dec <<len << "|";
    for(int i = 0; i < len  ; i++)
        {
        std::cout << " 0x" << std::setw(2);
        std::cout << std::setfill('0') << std::hex;
        std::cout << static_cast<int>(buf[i]);
        }
    std::cout <<" | \n";
}

std::string EcoNet::date(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);      
    std::stringstream ss; 
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ") ;
    return ss.str();
}

uint8_t EcoNet::crc(std::vector<uint8_t> &message)
{   
    uint8_t tmp = message.at(0);
    for(int i = 1 ; i < static_cast<int>(message.size()-2) ; i++ )
    {
        tmp = tmp^message.at(i);
    }
    return tmp;
}

void EcoNet::analyze_frame_ecoster(std::vector<uint8_t> &payload)
{  
    ecoster_payload.home_temp = retrun_float(payload, 16); 
    ecoster_payload.home_temp_target = retrun_float(payload, 20); 
    ecoster_payload.ecoster_1_temp = retrun_float(payload, 24); 
    ecoster_payload.ecoster_2_temp = retrun_float(payload,28); 
}

void EcoNet::analyze_frame_econet(std::vector<uint8_t> &payload)
{
if(payload.at(1))
    std::cout<<1;

}

void EcoNet::analyze_frame_ecomax_920P1(std::vector<uint8_t> &payload)
{   
    ecomax920_payload.operating_status = payload.at(29);
    ecomax920_payload.huw_temp = retrun_float(payload, 78);      
    ecomax920_payload.mixer_temp = retrun_float(payload, 82);                                             
    ecomax920_payload.weather_temp = retrun_float(payload, 86);  
    ecomax920_payload.boiler_return_temp = retrun_float(payload, 90);   
    ecomax920_payload.exhaust_temp = retrun_float(payload, 94); 
    ecomax920_payload.feader_temp = retrun_float(payload, 98);   
    ecomax920_payload.boiler_temp = retrun_float(payload, 102);      
    ecomax920_payload.flame_sensor = retrun_float(payload, 106);                                                   
    ecomax920_payload.upper_buffer_temp = retrun_float(payload, 110); 
    ecomax920_payload.lower_buffer_temp = retrun_float(payload, 114); 
    
    ecomax920_payload.huw_temp_target = static_cast<int>(payload.at(166));
    ecomax920_payload.boiler_temp_target = static_cast<int>(payload.at(172));
    ecomax920_payload.mixer_temp_target =  static_cast<int>(payload.at(166));
    ecomax920_payload.fuel_level = static_cast<int>(payload.at(217));
    ecomax920_payload.fan_out_power = static_cast<int>(payload.at(255));
    ecomax920_payload.fan_in_power = static_cast<int>(payload.at(254));
    ecomax920_payload.fuel_stream = retrun_float(payload, 260);
    ecomax920_payload.boiler_power_kw = retrun_float(payload, 256);
    ecomax920_payload.power_max_time = retrun_short(payload, 266); 
    ecomax920_payload.power_medium_time = retrun_short(payload, 268);
    ecomax920_payload.power_min_time = retrun_short(payload, 270);
    ecomax920_payload.feader_time = retrun_short(payload, 272);
    ecomax920_payload.ignisions = retrun_short(payload, 274);
    ecomax920_payload.ignisions_fails = retrun_short(payload, 276);
    /* to investigate: 
     float 219
     float 220


    */
}
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

short int EcoNet::retrun_short(std::vector<uint8_t> &payload, int p)
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
float EcoNet::get_huw_temp()
{
    return ecomax920_payload.huw_temp;
}
float EcoNet::get_feader_temp()
{
    return ecomax920_payload.feader_temp;
}
float EcoNet::get_boiler_temp()
{
    return ecomax920_payload.boiler_temp;
}
float EcoNet::get_weather_temp()
{
    return ecomax920_payload.weather_temp;
}
float EcoNet::get_exhaust_temp()
{
    return ecomax920_payload.exhaust_temp;
}
float EcoNet::get_mixer_temp()
{
    return ecomax920_payload.mixer_temp;
}
float EcoNet::get_boiler_return_temp()
{
    return ecomax920_payload.boiler_return_temp;
}
float EcoNet::get_upper_buffer_temp()
{
    return ecomax920_payload.upper_buffer_temp;
}
float EcoNet::get_lower_buffer_temp()
{
    return ecomax920_payload.lower_buffer_temp;
}
float EcoNet::get_flame_sensor()
{
    return ecomax920_payload.flame_sensor;
}
uint8_t EcoNet::get_huw_temp_target()
{
    return ecomax920_payload.huw_temp_target;
}
uint8_t EcoNet::get_boiler_temp_target()
{
    return ecomax920_payload.boiler_temp_target;
}
uint8_t EcoNet::get_mixer_temp_target()
{
    return ecomax920_payload.mixer_temp_target;
}
uint8_t EcoNet::get_fuel_level()
{
    return ecomax920_payload.fuel_level;
}
uint8_t EcoNet::get_fan_out_power()
{
    return ecomax920_payload.fan_out_power;
}
uint8_t EcoNet::get_fan_in_power()
{
    return ecomax920_payload.fan_in_power;
}
float EcoNet::get_fuel_stream()
{
    return ecomax920_payload.fuel_stream;
}
float EcoNet::get_boiler_power_kw()
{
    return ecomax920_payload.boiler_power_kw;
}
short EcoNet::get_power_max_time()
{
    return ecomax920_payload.power_max_time;
}
short EcoNet::get_power_medium_time()
{
    return ecomax920_payload.power_medium_time;
}
short EcoNet::get_power_min_time()
{
    return ecomax920_payload.power_min_time;
}
short EcoNet::get_feader_time()
{
    return ecomax920_payload.feader_time;
}
short EcoNet::get_ignisions()
{
    return ecomax920_payload.ignisions;
}
short EcoNet::get_ignisions_fails()
{
    return ecomax920_payload.ignisions_fails;
}

float EcoNet::get_ecoster_home_temp()
{
    return ecoster_payload.home_temp;
}
float EcoNet::get_ecoster_home_temp_target()
{
    return ecoster_payload.home_temp_target;
} 

void EcoNet::set_huw_temp()
{
    std::vector<uint8_t> buf = {0x68, 0x10, 0x00, 0x45, 0x56, 0x30, 0x05, 0x57, 0x01, 0x00, 0x04, 0x01 ,0x05, 0x36, 0x3e, 0x16};
    // std::vector<uint8_t> buf = {0x68 0x0d 0x00 0x45 0x56 0x30 0x05 0x56 0x04 0xff 0x00 0xee 0x16};
    // std::vector<uint8_t> buf = {0x68 0x0d 0x00 0x45 0x56 0x30 0x05 0x56 0x04 0xff 0xd6 0x38 0x16};
    serial.serial_send(buf);
}