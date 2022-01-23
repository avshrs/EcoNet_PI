#pragma once
#include <string>
#include "vars.h"
#include "USB_serial.h"

class EcoNet{
    private:
        USB_serial serial;

        TX_Buffer buf;
        RX_Buffer rx_buf;

        Ecomax920_payload ecomax920_payload;
        Ecoster_payload ecoster_payload;
        Econet_payload  econet_payload;

        uint8_t frame_begin = 0x68;
        uint8_t frame_end = 0x16;

        uint8_t econet_address = 0x56;
        uint8_t econet_frame = 0xb0;
        uint8_t econet_set_frame = 0x57;
        uint8_t econet_set_write_frame = 0x56; //??

        uint8_t eco____address = 0x50; //??


        uint8_t ecomax_address = 0x45;
        uint8_t ecomax_frame = 0x08;
        
        uint8_t ecoster_address = 0x51;
        uint8_t ecoster_frame = 0x89;

        std::map<uint8_t, std::string> operating_status_sting
        { 
            {0, "Turned Off"}, 
            {1, "Fire Up"}, 
            {2, "Work"}, //
            {3, "3"}, //
            {4, "Burning_Off"}, 
            {5, "Halted"}, //
            {6, "6"}, 
            {7, "7"}, 
            {8, "Cleaning"}, 
            {9, "9"}, 
            {10, "10"}, 
            
        };
    public:
        void init(std::string serialName, int boudrate, int lead_zero);
        void run();
       
    private:
        void print_buffer(uint8_t *buf, int len);
        std::string date();
        void analyze_frame_ecomax_920P1(std::vector<uint8_t> &payload);
        void analyze_frame_econet(std::vector<uint8_t> &payload);
        void analyze_frame_ecoster(std::vector<uint8_t> &payload);
        float retrun_float(std::vector<uint8_t> &payload, int position);
        short retrun_short(std::vector<uint8_t> &payload, int p);
        
        uint8_t crc(std::vector<uint8_t> &message);
        uint8_t crc_set(std::vector<uint8_t> &message);
    public:
        std::string get_operating_status();
        
        float get_huw_temp();
        float get_feader_temp();
        float get_boiler_temp();
        float get_weather_temp();
        float get_exhaust_temp();
        float get_mixer_temp();
        float get_boiler_return_temp();
        float get_upper_buffer_temp();
        float get_lower_buffer_temp();
        float get_flame_sensor();

        float get_ecoster_home_temp();
        float get_ecoster_home_temp_target();

        uint8_t get_huw_temp_target();
        uint8_t get_boiler_temp_target();
        uint8_t get_mixer_temp_target();
        uint8_t get_fuel_level();
        uint8_t get_fan_out_power();
        uint8_t get_fan_in_power();
        float get_fuel_stream();
        float get_boiler_power_kw();
        short get_power_max_time();
        short get_power_medium_time();
        short get_power_min_time();
        short get_feader_time();
        short get_ignisions();
        short get_ignisions_fails();

    public:
        void set_huw_temp(uint8_t temp);
        void set_huw_pump_mode(std::string pump_mode);
        void set_huw_temp_hysteresis(uint8_t hysteresis);
        void set_huw_container_disinfection(bool state);
        
        void set_boiler_temp(uint8_t temp);
        void set_boiler_on_off(bool state);
        
        void set_mixer_temp(uint8_t temp);
        
        void set_room_thermostat_summer_winter_mode(std::string state);
        void set_room_thermostat_night_temp(short temp);
        void set_room_thermostat_day_temp(short temp);
        void set_room_thermostat_operating_mode(std::string state);

};

