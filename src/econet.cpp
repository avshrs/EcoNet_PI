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
    while (true)
    {
        rx_buf.buf.clear();

        serial.serial_read(rx_buf);
        if(rx_buf.buf.at(0)==0x68 && rx_buf.buf.at(7)==0x08 && rx_buf.buf.at(4)==0x45)
        {
            buf.buf.insert(buf.buf.end(), rx_buf.buf.begin(), rx_buf.buf.end() );
            while(true)
            {
                serial.serial_read(rx_buf);
                buf.buf.insert(buf.buf.end(), rx_buf.buf.begin(), rx_buf.buf.end() );
                if ( std::find(rx_buf.buf.begin(), rx_buf.buf.end(), 0x16) != rx_buf.buf.end() )
                {
                    buf.buf.insert(buf.buf.end(), rx_buf.buf.begin(), rx_buf.buf.end() );
                    break;
                }
            }
            print_buffer(rx_buf.buf.data(), rx_buf.buf.size());
            analyze_frame(rx_buf);
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


void EcoNet::analyze_frame(RX_Buffer &rx_buffer)
{   

    eco_payload.payload_type = rx_buffer.buf.at(7);
    eco_payload.operating_status = rx_buffer.buf.at(40);
    eco_payload.cwu_temp = retrun_float(rx_buffer, 81);
    eco_payload.feader_temp = retrun_float(rx_buffer, 85);
    eco_payload.co_temp = retrun_float(rx_buffer, 89);
    eco_payload.weather_temp = retrun_float(rx_buffer, 97);
    eco_payload.exhoust_temp = retrun_float(rx_buffer, 101);                                                      
    eco_payload.mixer_temp = retrun_float(rx_buffer, 113);                                                   


}
float EcoNet::retrun_float(RX_Buffer &rx_buffer, int p)
{
union {
    float f;
    uint8_t ui[4];
 } u;

    for(int i = 0 ; i< 4 ; i++)
        u.ui[i] = rx_buffer.buf.at(i+p);
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
