#include "econet.h"
#include <iomanip>
#include <iostream>
#include <ctime>   // localtime
#include <stdlib.h>


void EcoNet::init(std::string serialName, int boudrate, int lead_zero)
{
        serial.serial_open(serialName.c_str(), boudrate, lead_zero);
}

void EcoNet::run()
{
    while (true)
    {
        rx_buf.buf.clear();
        tx_buf.buf.clear();

        serial.serial_read(rx_buf);
            if(rx_buf.buf.at(0)==0x68 && rx_buf.buf.at(7)==0x08)
            {
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
    eco_payload.cwu_temp = ((rx_buffer.buf.at(81)) | 
                            (rx_buffer.buf.at(82) << 8) | 
                            (rx_buffer.buf.at(82) << 16) | 
                            (rx_buffer.buf.at(84) << 24)) ;
    eco_payload.feader_temp = (rx_buffer.buf.at(85)) |
                              (rx_buffer.buf.at(86) << 8) | 
                              (rx_buffer.buf.at(87) << 16) | 
                              (rx_buffer.buf.at(88) << 24) ;
    eco_payload.co_temp = (rx_buffer.buf.at(89)) |
                          (rx_buffer.buf.at(90) << 8) | 
                          (rx_buffer.buf.at(91) << 16) | 
                          (rx_buffer.buf.at(92) << 24) ;
    eco_payload.weather_temp = (rx_buffer.buf.at(97)) |
                               (rx_buffer.buf.at(98) << 8) | 
                               (rx_buffer.buf.at(99) << 16) | 
                               (rx_buffer.buf.at(100) << 24) ;
    eco_payload.exhoust_temp = (rx_buffer.buf.at(101)) |
                               (rx_buffer.buf.at(102) << 8) | 
                               (rx_buffer.buf.at(103) << 16) | 
                               (rx_buffer.buf.at(104) << 24) ;                                                      
    eco_payload.mixer_temp = (rx_buffer.buf.at(113)) |
                             (rx_buffer.buf.at(114) << 8) | 
                             (rx_buffer.buf.at(115) << 16) | 
                             (rx_buffer.buf.at(116) << 24) ;                                                      


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