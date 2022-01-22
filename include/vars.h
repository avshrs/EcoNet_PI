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



struct payload{
    uint8_t payload_type = 0;      
    uint8_t operating_status = 0;   
    float  cwu_temp = 0;        
    float  feader_temp = 0;     
    float  co_temp = 0;        
    float  outside_temp = 0;        
    float  weather_temp = 0;   
    float  exhoust_temp = 0;    
    float  mixer_temp = 0;      
    uint32_t pomp_states = 0;
    uint32_t pomp_sets = 0;
    uint8_t cwu_temp_set = 0; 
    uint8_t co_temp_set = 0;  
    uint8_t co_status = 0;  
    uint8_t cwu_status = 0; 
    uint8_t alarms_no = 0;
    uint8_t fuel_level = 0;  
    uint8_t transmission = 0;
    float fanPower = 0;    
    uint8_t boiler_power = 0;
    float boiler_power_kw = 0;    
    float fuel_stream = 0;  
    uint8_t thermostat = 0;
    float versionInfo = 0;    
    float moduleBSoftVer = 0;    
    float moduleCSoftVer = 0;    
    float moduleLambdaSoftVer = 0;    
    float moduleEcoSTERSoftVer = 0;    
    float modulePanelSoftVer = 0;    
    float lambdaStatus = 0;    
    float lambdaSet = 0;   
    float lambda_level = 0;   
    float oxygen = 0;   
    uint16_t power100_time = 0;   
    uint16_t power50_time = 0; 
    uint16_t power30_time = 0; 
    
    uint16_t feader_time = 0; 
    uint16_t ignisions = 0; 

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

