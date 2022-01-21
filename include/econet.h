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
            {0, "WYLACZONY"}, 
            {1, "ROZPALANIE"}, 
            {2, "STABILIZACJA"}, 
            {3, "PRACA"}, 
            {4, "NADZOR"}, 
            {5, "WYGASZANIE"}, 
            {6, "POSTÓJ"}, 
            {7, "WYGASZANIE_NA_ZĄDANIE"}, 
            {9, "ALARM"}, 
            {10, "ROZSZCZELNIENIE"}, 
            
        };
    public:
        void print_buffer(uint8_t *buf, int len);
        std::string date();
        void analyze_frame(RX_Buffer &rx_buffer);
        std::string get_operating_status();
        float get_cwu_temp();
        float get_feader_temp();
        float get_co_temp();
        float get_weather_temp();
        float get_exhoust_temp();
        float get_mixer_temp();
        float get_pomp_states();
        float get_pomp_sets();
        uint8_t get_cwu_temp_set();
        uint8_t get_co_temp_set();
        uint8_t get_co_status();
        uint8_t get_cwu_status();
        uint8_t get_alarms_no();
        uint8_t get_fuel_level();
        uint8_t get_transmission();
        float get_fanPower();
        uint8_t get_boiler_power();
        float get_boiler_power_kw();
        float get_fuel_stream();
        uint8_t get_thermostat();
        float get_versionInfo();
        float get_moduleBSoftVer();
        float get_moduleCSoftVer();
        float get_moduleLambdaSoftVer();
        float get_moduleEcoSTERSoftVer();
        float get_modulePanelSoftVer();
        float get_lambda_level();
        float get_oxygen();
        short get_power100_time();
        short get_power50_time();
        short get_power30_time();
        short get_feader_time();
        short get_ignisions();



};
