#pragma once
#include "vars.h"
#include <vector>

class Config_manager{
    private:
        Mqtt_config mqtt_config;
        EcoNet_cfg eco_config;

    public:
        void read_config();
        std::string date();
        std::string get_mqtt_ClientId();
        std::string get_mqtt_ip();
        int         get_mqtt_port();
        std::string get_mqtt_password();
        std::string get_mqtt_username();
        std::string get_mqtt_keepAliveTopic();
        std::string get_mqtt_keepAliveMsg();
        std::string get_mqtt_Substring();
        std::string get_mqtt_Pubstring();

        std::string get_eco_serial_file();
        int         get_eco_boudrate();
        int         get_eco_lead_zeros();
        
     
};
