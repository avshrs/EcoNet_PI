#pragma once
#include "vars.h"
#include <vector>

class Config_manager{
    private:
        Mqtt_config mqtt_config;
        EcoNet_cfg eco_config;
        Econet_Mqtt econet_mqtt;
        std::string config_path;

    public:
        void register_config(std::string config_path_);
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


        std::string sub_get_operating_status();
        std::string sub_get_huw_temp();
        std::string sub_get_feeder_temp();
        std::string sub_get_boiler_temp();
        std::string sub_get_weather_temp();
        std::string sub_get_exhaust_temp();
        std::string sub_get_mixer_temp();
        std::string sub_get_boiler_return_temp();
        std::string sub_get_upper_buffer_temp();
        std::string sub_get_lower_buffer_temp();
        std::string sub_get_flame_sensor();
        std::string sub_get_ecoster_home_temp();
        std::string sub_get_ecoster_home_temp_target();
        std::string sub_get_huw_temp_target();
        std::string sub_get_boiler_temp_target();
        std::string sub_get_mixer_temp_target();
        std::string sub_get_fuel_level();
        std::string sub_get_fan_out_power();
        std::string sub_get_fan_in_power();
        std::string sub_get_huw_pomp_state();
        std::string sub_get_boiler_pomp_state();
        std::string sub_get_fuel_stream();
        std::string sub_get_boiler_power_kw();
        std::string sub_get_power_max_time();
        std::string sub_get_power_medium_time();
        std::string sub_get_power_min_time();
        std::string sub_get_feeder_time();
        std::string sub_get_ignitions();
        std::string sub_get_ignitions_fails();
        std::string sub_get_huw_pump_mode();
        std::string sub_get_huw_temp_hysteresis();
        std::string sub_get_huw_container_disinfection();
        std::string sub_get_boiler_on_off();
        std::string sub_get_boiler_max_power_kw();
        std::string sub_get_boiler_mid_power_kw();
        std::string sub_get_boiler_min_power_kw();
        std::string sub_get_boiler_max_power_fan();
        std::string sub_get_boiler_mid_power_fan();
        std::string sub_get_boiler_min_power_fan();
        std::string sub_get_room_thermostat_summer_winter_mode();
        std::string sub_get_room_thermostat_night_temp();
        std::string sub_get_room_thermostat_day_temp();
        std::string sub_get_room_thermostat_operating_mode();
        std::string sub_get_room_thermostat_hysteresis();





















};
