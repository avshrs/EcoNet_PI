#include <iostream>
#include "econet.h"
#include "Config_manager.h"
#include <thread>

void th1(EcoNet *econet){
   econet->run();    
}

int main()
{
    Config_manager cfg;
    cfg.read_config();

    EcoNet econet;
    std::string serial_file_name = cfg.get_eco_serial_file();
    int rs_lead_zero = cfg.get_eco_lead_zeros();
    int boudrate = cfg.get_eco_boudrate();
    econet.init(serial_file_name.c_str(), boudrate, rs_lead_zero);
    
    std::thread Hoermann_door_service(th1, &econet);
    while (true)
    {
        std::cout<< "oper stat: "<< econet.get_operating_status()  <<std::endl;
        std::cout<< "CO temp: "<< econet.get_co_temp()  <<std::endl;
        std::cout<< "CWU temp: "<< econet.get_cwu_temp()     <<std::endl;
        std::cout<< "Feader temp: "<< econet.get_feader_temp()    <<std::endl;
        std::cout<< "Wather temp: "<< econet.get_weather_temp()    <<std::endl;
        std::cout<< "Exhoust temp: "<< econet.get_exhoust_temp()   <<std::endl;
        std::cout<< "mixer temp: "<< econet.get_mixer_temp()   <<std::endl;
        std::cout<< "outside temp: "<< econet.get_outside_temp()   <<std::endl;
        sleep(1);
    }
    



return 1;
}


