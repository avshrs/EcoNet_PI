#pragma once
#include <cstdio>
#include <unistd.h>
#include <chrono>
#include <string>
#include <vector>
#include <map>
struct TX_Buffer{
    
    std::vector<uint8_t> buf;
    TX_Buffer(){buf.reserve(1024);}

};
struct RX_Buffer{
    RX_Buffer(){buf.reserve(1024);}
    std::vector<uint8_t> buf;
};

struct EcoNet_cfg{
    std::string serial_file;
    int boudrate;
    int remove_lead_zero;
    
    
};
struct Mqtt_config{
    std::string ClientId;
    std::string ServerIp;
    std::string username;
    std::string password;
    int serverPort;
    std::string keepAliveTopic;
    std::string keepAliveMsg;
    std::string Substring;
    std::string Pubstring;


};

struct Ecoster_payload{
    float home_temp_target = 0; 
    float home_temp = 0;
    float ecoster_1_temp = 0;
    float ecoster_2_temp = 0;
};
struct Econet_payload{
};

struct Econet_Mqtt
{
    std::string pub_huw_temp;
    std::string pub_huw_temp;
    std::string pub_huw_pump_mode;
    std::string pub_huw_temp_hysteresis;
    std::string pub_huw_container_disinfection;
    std::string pub_boiler_temp;
    std::string pub_boiler_on_off;
    std::string pub_boiler_max_power_kw;
    std::string pub_boiler_mid_power_kw;
    std::string pub_boiler_min_power_kw;
    std::string pub_boiler_max_power_fan;
    std::string pub_boiler_mid_power_fan;
    std::string pub_boiler_min_power_fan;
    std::string pub_mixer_temp;
    std::string pub_room_thermostat_summer_winter_mode;
    std::string pub_room_thermostat_night_temp;
    std::string pub_room_thermostat_day_temp;
    std::string pub_room_thermostat_operating_mode;
    std::string pub_room_thermostat_hysteresis;
};


struct Ecomax920_payload{

    uint8_t payload_type = 0;      
    uint8_t operating_status = 0;   
    float  huw_temp = 0;        
    float  feader_temp = 0;     
    float  boiler_temp = 0;        
    float  boiler_return_temp = 0;
    float  flame_sensor = 0;
    float  upper_buffer_temp = 0;
    float  lower_buffer_temp = 0;
    float  weather_temp = 0;   
    float  exhaust_temp = 0;    
    float  mixer_temp = 0;      
    float boiler_power_kw = 0;    
    float fuel_stream = 0;  
    uint8_t huw_temp_target = 0; 
    uint8_t boiler_temp_target = 0;  
    uint8_t mixer_temp_target = 0;  

    uint8_t fuel_level = 0;  
    uint8_t transmission = 0;

    uint8_t fan_in_power = 0;    
    uint8_t fan_out_power = 0;    
    uint8_t boiler_power = 0;
    uint8_t huw_pomp_state = 0;
    uint8_t boiler_pomp_state = 0;

    short power_max_time = 0;   
    short power_medium_time = 0; 
    short power_min_time = 0; 
    short feader_time = 0; 
    short ignisions = 0; 
    short ignisions_fails = 0; 

};


struct packet_structure{
    uint8_t frame_type = 0;
    uint16_t frame_size = 0;
    uint8_t dst_address = 0;
    uint8_t src_address = 0;
    uint8_t sender_type = 0;
    uint8_t econet_version = 0;
    uint8_t crc = 0;

};

