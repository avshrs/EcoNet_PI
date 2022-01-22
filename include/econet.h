#pragma once
#include <string>
#include "vars.h"
#include "USB_serial.h"

class EcoNet{
    public:
        TX_Buffer buf;
        RX_Buffer rx_buf;
        payload eco_payload;
        USB_serial serial;
        
        void init(std::string serialName, int boudrate, int lead_zero);
        void run();
        std::map<uint8_t, std::string> operating_status_sting
        { 
            {0, "Turned Off"}, 
            {1, "1"}, 
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
    private:
        void print_buffer(uint8_t *buf, int len);
        std::string date();
        void analyze_frame(std::vector<uint8_t> &payload);
        float retrun_float(std::vector<uint8_t> &payload, int position);
        short retrun_short(std::vector<uint8_t> &payload, int p);
        
        uint8_t crc(std::vector<uint8_t> &message);
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




};
