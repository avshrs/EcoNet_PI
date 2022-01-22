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

        serial.serial_read_bytes(header, 8); // read frame header
        if(header.at(0)==0x68 && header.at(7)==0x08 && header.at(4)==0x45)
        {
            short paylod_len = ((header.at(1)) | (header.at(2)<<8));
       
            for(int i =0 ; i< paylod_len - 8; i++)
                serial.serial_read_byte(payload);

            message.insert(message.end(), header.begin(), header.end());
            message.insert(message.end(), payload.begin(), payload.end());
            
            if(crc(message) == static_cast<uint8_t>(message.at(message.size()-2)))
                
                {
                
                print_buffer(payload.data(), payload.size() );
                analyze_frame(payload);
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
    uint8_t tmp2[1] = {tmp};
    print_buffer(tmp2, 1);
    return tmp;
}


void EcoNet::analyze_frame(std::vector<uint8_t> &payload)
{   
    eco_payload.operating_status = payload.at(33);
    eco_payload.huw_temp = retrun_float(payload, 78);      
    eco_payload.mixer_temp = retrun_float(payload, 82);                                             
    eco_payload.weather_temp = retrun_float(payload, 86);  
    eco_payload.boiler_return_temp = retrun_float(payload, 90);   
    eco_payload.exhaust_temp = retrun_float(payload, 94); 
    eco_payload.feader_temp = retrun_float(payload, 98);   
    eco_payload.boiler_temp = retrun_float(payload, 102);      
    eco_payload.flame_sensor = retrun_float(payload, 106);                                                   
    eco_payload.upper_buffer_temp = retrun_float(payload, 110); 
    eco_payload.lower_buffer_temp = retrun_float(payload, 114); 
    
    eco_payload.huw_temp_target = static_cast<int>(payload.at(166));
    eco_payload.boiler_temp_target = static_cast<int>(payload.at(172));
    eco_payload.mixer_temp_target =  static_cast<int>(payload.at(166));
    eco_payload.fuel_level = static_cast<int>(payload.at(216));
    eco_payload.fan_out_power = static_cast<int>(payload.at(255));
    eco_payload.fan_in_power = static_cast<int>(payload.at(254));
    eco_payload.fuel_stream = retrun_float(payload, 260);
    eco_payload.boiler_power_kw = retrun_float(payload, 256);
    eco_payload.power_max_time = retrun_short(payload, 266); 
    eco_payload.power_medium_time = retrun_short(payload, 268);
    eco_payload.power_min_time = retrun_short(payload, 270);
    eco_payload.feader_time = retrun_short(payload, 272);
    eco_payload.ignisions = retrun_short(payload, 274);
    eco_payload.ignisions_fails = retrun_short(payload, 276);
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
    return operating_status_sting.at(eco_payload.operating_status);
}
float EcoNet::get_huw_temp()
{
    return eco_payload.huw_temp;
}
float EcoNet::get_feader_temp()
{
    return eco_payload.feader_temp;
}
float EcoNet::get_boiler_temp()
{
    return eco_payload.boiler_temp;
}
float EcoNet::get_weather_temp()
{
    return eco_payload.weather_temp;
}
float EcoNet::get_exhaust_temp()
{
    return eco_payload.exhaust_temp;
}
float EcoNet::get_mixer_temp()
{
    return eco_payload.mixer_temp;
}
float EcoNet::get_boiler_return_temp()
{
    return eco_payload.boiler_return_temp;
}
float EcoNet::get_upper_buffer_temp()
{
    return eco_payload.upper_buffer_temp;
}
float EcoNet::get_lower_buffer_temp()
{
    return eco_payload.lower_buffer_temp;
}
float EcoNet::get_flame_sensor()
{
    return eco_payload.flame_sensor;
}
uint8_t EcoNet::get_huw_temp_target()
{
    return eco_payload.huw_temp_target;
}
uint8_t EcoNet::get_boiler_temp_target()
{
    return eco_payload.boiler_temp_target;
}
uint8_t EcoNet::get_mixer_temp_target()
{
    return eco_payload.mixer_temp_target;
}
uint8_t EcoNet::get_fuel_level()
{
    return eco_payload.fuel_level;
}
uint8_t EcoNet::get_fan_out_power()
{
    return eco_payload.fan_out_power;
}
uint8_t EcoNet::get_fan_in_power()
{
    return eco_payload.fan_in_power;
}
float EcoNet::get_fuel_stream()
{
    return eco_payload.fuel_stream;
}
float EcoNet::get_boiler_power_kw()
{
    return eco_payload.boiler_power_kw;
}
short EcoNet::get_power_max_time()
{
    return eco_payload.power_max_time;
}
short EcoNet::get_power_medium_time()
{
    return eco_payload.power_medium_time;
}
short EcoNet::get_power_min_time()
{
    return eco_payload.power_min_time;
}
short EcoNet::get_feader_time()
{
    return eco_payload.feader_time;
}
short EcoNet::get_ignisions()
{
    return eco_payload.ignisions;
}
short EcoNet::get_ignisions_fails()
{
    return eco_payload.ignisions_fails;
}