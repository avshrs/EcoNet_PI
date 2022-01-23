#pragma once
#include "vars.h"
#include <vector>

class Config_manager{
    private:
        Mqtt_config mqtt_config;
        EcoNet_cfg eco_config;
        Econet_Mqtt econet_mqtt;

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
    
        std::string get_huw_temp();
        std::string get_huw_pump_mode();
        std::string get_huw_temp_hysteresis();
        std::string get_huw_container_disinfection();
        std::string get_boiler_temp();
        std::string get_boiler_on_off();
        std::string get_boiler_max_power_kw();
        std::string get_boiler_mid_power_kw();
        std::string get_boiler_min_power_kw();
        std::string get_boiler_max_power_fan();
        std::string get_boiler_mid_power_fan();
        std::string get_boiler_min_power_fan();
        std::string get_mixer_temp();
        std::string get_room_thermostat_summer_winter_mode();
        std::string get_room_thermostat_night_temp();
        std::string get_room_thermostat_day_temp();
        std::string get_room_thermostat_operating_mode();
        std::string get_room_thermostat_hysteresis();






















};
