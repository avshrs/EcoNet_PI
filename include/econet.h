#pragma once
#include <string>
#include "vars.h"
#include "USB_serial.h"
#include <chrono>
#include "Config_manager.h"

class Mqtt_Client;

class EcoNet{
    private:
        USB_serial serial;
        Mqtt_Client *mqtt;
        Config_manager *cfg;
        Econet_Mqtt econet_set_values;
        
        std::vector<uint8_t> deb1;
        std::vector<uint8_t> deb2;
        std::vector<uint8_t> deb3;
        std::vector<uint8_t> deb11;
        std::vector<uint8_t> deb22;
        std::vector<uint8_t> deb33;

        std::chrono::high_resolution_clock timer;
        using mi = std::chrono::duration<float, std::micro>;
        
        Ecomax_920_Live_Data_Frame_payload ecomax920_payload;
        Ecomax_920_Live_Data_Frame_payload ecomax920_buffer;

        Ecomax_settings_Frame_payload ecomax920_settings_payload;
        Ecomax_settings_Frame_payload ecomax920_settings_buffer;

        Ecoster_Live_Data_Frame_payload ecoster_payload;
        Ecoster_Live_Data_Frame_payload ecoster_buffer;
        
        Ecoster_Settings_Frame_payload ecoster_settings_payload;
        Ecoster_Settings_Frame_payload ecoster_settings_buffer;
        
        uint8_t frame_begin = 0x68;
        uint8_t frame_end = 0x16;

        uint8_t econet_address = 0x56;
        uint8_t econet_frame = 0xb0;
        uint8_t econet_set_frame = 0x57;
        uint8_t econet_set_write_frame = 0x56; //??

        uint8_t eco____address = 0x50; //??

        uint8_t ecomax_address = 0x45; // master address
        uint8_t ecomax_live_data_frame = 0x08; // broadcast with live data 
        uint8_t ecomax_frame2 = 0x35; // some kind of broadcast 
        uint8_t ecomax_frame3 = 0x0a; // ask slaves for data / hartbeet  
        uint8_t ecomax_settings_frame = 0xe1; 
        
        uint8_t ecoster_address = 0x51;
        uint8_t ecoster_frame = 0x89;
        uint8_t ecoster_settings_frame = 0xa7;

        std::map<uint8_t, std::string> operating_status_sting
        { 
            {0, "Turned Off"}, 
            {1, "Fire Up"}, 
            {2, "Work"},
            {3, "3"},
            {4, "Burning_Off"}, 
            {5, "Halted"}, 
            {6, "6"}, 
            {7, "7"}, 
            {8, "Cleaning"}, 
            {9, "9"}, 
            {10, "10"}, 
            
        };
    public:
        void init(std::string serialName, int boudrate, int lead_zero);
        void run();
        void register_mqtt(Mqtt_Client *mqtt_);
        void register_cfg(Config_manager *cfg_);
    private:

        void print_buffer(uint8_t *buf, int len);
        void show_diff(std::vector<uint8_t> payload);
        void show_diff2(std::vector<uint8_t> payload);
        std::string date();
        void analyze_frame_ecomax_920P1(std::vector<uint8_t> &payload);
        void analyze_frame_ecomax_920P1_settings(std::vector<uint8_t> &payload);
        void analyze_frame_ecoster_settings(std::vector<uint8_t> &payload);

        void analyze_frame_econet(std::vector<uint8_t> &payload);
        void analyze_frame_ecoster(std::vector<uint8_t> &payload);
        float retrun_float(std::vector<uint8_t> &payload, int position);
        short retrun_short(std::vector<uint8_t> &payload, int p);
        
        uint8_t crc(std::vector<uint8_t> &message);
        uint8_t crc_set(std::vector<uint8_t> &message);
        void update_statuses();
    public:
        std::string get_operating_status();
        
        std::string get_huw_temp();
        std::string get_feeder_temp();
        std::string get_boiler_temp();
        std::string get_weather_temp();
        std::string get_exhaust_temp();
        std::string get_mixer_temp();
        std::string get_boiler_return_temp();
        std::string get_upper_buffer_temp();
        std::string get_lower_buffer_temp();
        std::string get_flame_sensor();

        std::string get_ecoster_home_temp();
        std::string get_ecoster_home_temp_target();

        std::string get_huw_temp_target();
        std::string get_boiler_temp_target();
        std::string get_mixer_temp_target();
        std::string get_fuel_level();
        std::string get_fan_out_power();
        std::string get_fan_in_power();
        std::string get_huw_pomp_state();
        std::string get_boiler_pomp_state();
        std::string get_fuel_stream();
        std::string get_boiler_power_kw();
        std::string get_power_max_time();
        std::string get_power_medium_time();
        std::string get_power_min_time();
        std::string get_feeder_time();
        std::string get_ignitions();
        std::string get_ignitions_fails();

    public:
        std::string get_huw_pump_mode();
        std::string get_huw_temp_hysteresis();
        std::string get_huw_container_disinfection();
        
        std::string get_boiler_on_off();
        std::string get_boiler_max_power_kw();
        std::string get_boiler_mid_power_kw();
        std::string get_boiler_min_power_kw();
        std::string get_boiler_max_power_fan();
        std::string get_boiler_mid_power_fan();
        std::string get_boiler_min_power_fan();
        
        std::string get_room_thermostat_summer_winter_mode();
        std::string get_room_thermostat_night_temp();
        std::string get_room_thermostat_day_temp();
        std::string get_room_thermostat_operating_mode();
        std::string get_room_thermostat_hysteresis();

    public:
        void set_huw_temp(uint8_t temp);
        void set_huw_pump_mode(std::string pump_mode);
        void set_huw_temp_hysteresis(uint8_t hysteresis);
        void set_huw_container_disinfection(bool state);
        
        void set_boiler_temp(uint8_t temp);
        void set_boiler_on_off(bool state);
        void set_boiler_max_power_kw(uint8_t power_kw);
        void set_boiler_mid_power_kw(uint8_t power_kw);
        void set_boiler_min_power_kw(uint8_t power_kw);
        void set_boiler_max_power_fan(uint8_t fun_max);
        void set_boiler_mid_power_fan(uint8_t fun_max);
        void set_boiler_min_power_fan(uint8_t fun_max);
        
        void set_mixer_temp(uint8_t temp);
        
        void set_room_thermostat_summer_winter_mode(std::string state);
        void set_room_thermostat_night_temp(float temp);
        void set_room_thermostat_day_temp(float temp);
        void set_room_thermostat_operating_mode(std::string state);
        void set_room_thermostat_hysteresis(float hysteresis);
    
};

