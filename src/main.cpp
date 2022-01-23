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

    sleep(1);
    econet.set_huw_temp();
    while (true)
    {
        std::cout<< "--------------------------------"<< std::endl;
        std::cout<< "oper stat: "<< econet.get_operating_status()  <<std::endl;
        std::cout<< "CO temp: "<< econet.get_boiler_temp()  <<std::endl;
        std::cout<< "CWU temp: "<< econet.get_huw_temp()     <<std::endl;
        std::cout<< "Feader temp: "<< econet.get_feader_temp()    <<std::endl;
        std::cout<< "Wather temp: "<< econet.get_weather_temp()    <<std::endl;
        std::cout<< "Exhoust temp: "<< econet.get_exhaust_temp()   <<std::endl;
        std::cout<< "mixer temp: "<< econet.get_mixer_temp()   <<std::endl;
        std::cout<< "return temp: "<< econet.get_boiler_return_temp()   <<std::endl;
        std::cout<< "get_upper_buffer_temp temp: "<< econet.get_upper_buffer_temp()   <<std::endl;
        std::cout<< "get_lower_buffer_temp temp: "<< econet.get_lower_buffer_temp()   <<std::endl;
        std::cout<< "flame : "<< econet.get_flame_sensor()   <<std::endl;

        std::cout<< "get_huw_temp_target : "<< std::dec <<static_cast<int>(econet.get_huw_temp_target() )  <<std::endl;
        std::cout<< "get_boiler_temp_target : "<< std::dec << static_cast<int>(econet.get_boiler_temp_target()  ) <<std::endl;
        std::cout<< "get_mixer_temp_target : "<< std::dec << static_cast<int>(econet.get_mixer_temp_target() )  <<std::endl;
        std::cout<< "get_fuel_level : "<< std::dec << static_cast<int>(econet.get_fuel_level())   <<std::endl;
        std::cout<< "get_fan_out_power : "<< std::dec << static_cast<int>(econet.get_fan_out_power()   )<<std::endl;
        std::cout<< "get_fan_in_power : "<< std::dec << static_cast<int>(econet.get_fan_in_power() )  <<std::endl;
        std::cout<< "get_fuel_stream : "<< std::dec << static_cast<float>(econet.get_fuel_stream() )  <<std::endl;
        std::cout<< "get_boiler_power_kw : "<< std::dec << static_cast<float>(econet.get_boiler_power_kw() )  <<std::endl;
        std::cout<< "get_power_max_time : "<< std::dec << static_cast<int>(econet.get_power_max_time())   <<std::endl;
        std::cout<< "get_power_medium_time : "<< std::dec << static_cast<int>(econet.get_power_medium_time())   <<std::endl;
        std::cout<< "get_power_min_time : "<< std::dec << static_cast<int>(econet.get_power_min_time())   <<std::endl;
        std::cout<< "get_feader_time : "<< std::dec << static_cast<int>(econet.get_feader_time())   <<std::endl;
        std::cout<< "get_ignisions : "<< std::dec << static_cast<int>(econet.get_ignisions())   <<std::endl;
        std::cout<< "get_ignisions_fails : "<< std::dec << static_cast<int>(econet.get_ignisions_fails())   <<std::endl;
 
        std::cout<< "get_ecoster_home_temp : "<< std::dec << static_cast<float>(econet.get_ecoster_home_temp())   <<std::endl;
        std::cout<< "get_ecoster_home_temp_target : "<< std::dec << static_cast<float>(econet.get_ecoster_home_temp_target())   <<std::endl;
        
        

        sleep(1);
    }
    



return 1;
}


