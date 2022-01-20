#pragma once
#include <cstdio>
#include <unistd.h>
#include <chrono>
#include <string>
#include <vector>

struct TX_Buffer{
    
    std::vector<uint8_t> buf;
    TX_Buffer(){buf.reserve(64);}

};
struct RX_Buffer{
    RX_Buffer(){buf.reserve(64);}
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
