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
            payload.push_back(header.at(7));
            print_buffer(header.data(), header.size());
            for(int i =0 ; i< paylod_len - 8; i++)
                serial.serial_read_byte(payload);

            message.insert(message.end(), header.begin(), header.end());
            message.insert(message.end(), payload.begin(), payload.end());
            if(crc(message) == static_cast<uint8_t>(payload.at(paylod_len-2)))
                
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
    for(int i = 1 ; i< message.size() ; i++ )
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
    eco_payload.cwu_temp = retrun_float(payload, 74);
    eco_payload.feader_temp = retrun_float(payload, 78);
    eco_payload.co_temp = retrun_float(payload, 82);
    eco_payload.weather_temp = retrun_float(payload, 90);
    eco_payload.exhoust_temp = retrun_float(payload, 94);                                                      
    eco_payload.mixer_temp = retrun_float(payload, 106);                                                   
    eco_payload.outside_temp = retrun_float(payload, 110);                                                   

}
float EcoNet::retrun_float(std::vector<uint8_t> &payload, int p)
{
    union {
        float f;
        uint32_t ui;
    } u;
    u.ui = (payload.at(p) << 24) | (payload.at(p+1) << 16) | 
           (payload.at(p+2) << 8) | (payload.at(p+3) );
    return u.f;
}

std::string EcoNet::get_operating_status()
{
    return operating_status_sting.at(eco_payload.operating_status);
    
}
float EcoNet::get_cwu_temp()
{
    return eco_payload.cwu_temp;
}
float EcoNet::get_feader_temp()
{
    return eco_payload.feader_temp;
}
float EcoNet::get_co_temp()
{
    return eco_payload.co_temp;
}
float EcoNet::get_weather_temp()
{
    return eco_payload.weather_temp;
}
float EcoNet::get_exhoust_temp()
{
    return eco_payload.exhoust_temp;
}
float EcoNet::get_mixer_temp()
{
    return eco_payload.mixer_temp;
}
float EcoNet::get_outside_temp()
{
    return eco_payload.outside_temp;
}
