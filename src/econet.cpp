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
        
        for(auto const& value: rx_buf.buf){
            if(value==0x68)
            {
                std::cout<<date()<< "ramka start: ";
                print_buffer(rx_buf.buf.data(),rx_buf.buf.size());
            }
            else    
            print_buffer(rx_buf.buf.data(),rx_buf.buf.size());

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
