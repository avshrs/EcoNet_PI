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
            if(rx_buf.buf.at(0)==0x68)
            {
                std::cout<<date()<< "\nramka start-----------------------------------------------------------------------------------------: \n";
                break;
            }

        }
                print_buffer(rx_buf.buf.data(),rx_buf.buf.size());        

                                    
            // 0000: 68 0a 00 52 45 fc 30 40  f9 16  Lower buffer temperature 52.9                                 
            // 0000: 68 0a 00 53 45 fc 30 40  f8 16  Upper buffer temperature 53.6                                  
            // 0000: 68 0a 00 04 45 fc 30 40  af 16  ? outside temp?                                  
            // 0000: 68 0a 00 55 45 fc 30 0a  b4 16  set temp on buffer
                 
                 
            //       1  2  3  4  5  6   7  8  9   10
            // 0000: 68 10 00 82 69 252 48 64 259 16  Lower buffer temperature 52.9                                 
            // 0000: 68 10 00 83 69 252 48 64 248 16  Upper buffer temperature 53.6                                  
            // 0000: 68 10 00  4 69 252 48 64 175 16  ? outside temp?                                  
            // 0000: 68 10 00 85 69 252 48 10 180 16  set temp on buffer
            // 1 ramka 
            // 2 długość ramki 
            // 3 ?
            // 4 temp? 
            // ...
            // 9 checksum?
            // 10 znak końca ramki 
        
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
