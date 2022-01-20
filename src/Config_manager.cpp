#include "Config_manager.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

std::string Config_manager::date(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);      
    std::stringstream ss; 
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ") ;
    return ss.str();
}

void Config_manager::read_config(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    

  
    
    std::cout << date() << "Loading Settings" << std::endl;
    mqtt_config.ClientId = config["mqtt"]["ClientId"].as<std::string>();
    mqtt_config.ServerIp = config["mqtt"]["ServerIp"].as<std::string>();
    mqtt_config.username = config["mqtt"]["username"].as<std::string>();
    mqtt_config.password = config["mqtt"]["password"].as<std::string>();
    mqtt_config.serverPort = config["mqtt"]["serverPort"].as<int>();
    
    mqtt_config.keepAliveTopic = config["mqtt"]["keepAliveTopic"].as<std::string>();
    mqtt_config.keepAliveMsg = config["mqtt"]["keepAliveMsg"].as<std::string>();
    
    mqtt_config.Substring = config["mqtt"]["Substring"].as<std::string>();
    mqtt_config.Pubstring = config["mqtt"]["Pubstring"].as<std::string>();

    eco_config.serial_file = config["hoermann"]["serial_file"].as<std::string>();
    eco_config.boudrate = config["hoermann"]["boudrate"].as<int>();
    eco_config.remove_lead_zero = config["hoermann"]["remove_lead_zero"].as<int>();
    std::cout << date() << "Settings Loaded" << std::endl;
}
    

std::string Config_manager::get_mqtt_ClientId(){
    return  mqtt_config.ClientId;
}
std::string Config_manager::get_mqtt_ip(){
    return  mqtt_config.ServerIp;
}
int Config_manager::get_mqtt_port(){
    return  mqtt_config.serverPort;
}
std::string Config_manager::get_mqtt_password(){
    return  mqtt_config.password;
}
std::string Config_manager::get_mqtt_username(){
    return  mqtt_config.username;
}
std::string Config_manager::get_mqtt_keepAliveTopic(){
    return  mqtt_config.keepAliveTopic;
}
std::string Config_manager::get_mqtt_keepAliveMsg(){
    return  mqtt_config.keepAliveMsg;
}
std::string Config_manager::get_mqtt_Substring(){
    return  mqtt_config.Substring;
}
std::string Config_manager::get_mqtt_Pubstring(){
    return  mqtt_config.Pubstring;
}
std::string Config_manager::get_eco_serial_file()
{
    return  eco_config.serial_file;
}
int Config_manager::get_eco_boudrate()
{
    return  eco_config.boudrate;
}
int Config_manager::get_eco_lead_zeros()
{
    return  eco_config.remove_lead_zero;
}