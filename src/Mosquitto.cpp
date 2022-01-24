#include "Mosquitto.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


std::string Mqtt_Client::date(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);      
    std::stringstream ss; 
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ") ;
    return ss.str();
}


Mqtt_Client::Mqtt_Client(const char *id, const char *host, int port, const char *username, const char *password) : mosquittopp(id)
{
    int keepalive = 60;
    
    username_pw_set(username, password);
    connect(host, port, keepalive);
}

void Mqtt_Client::client_loop_forever(){
    
        reconnect_delay_set(5, 1000000, true);
        loop_forever();
}

void Mqtt_Client::register_subs()
{
    std::string sub;
    sub = cfg->get_huw_temp();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_huw_pump_mode();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_huw_temp_hysteresis();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_huw_container_disinfection();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_temp();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_on_off();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_max_power_kw();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_mid_power_kw();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_min_power_kw();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_max_power_fan();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_mid_power_fan();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_boiler_min_power_fan();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_mixer_temp();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_room_thermostat_summer_winter_mode();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_room_thermostat_night_temp();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_room_thermostat_day_temp();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_room_thermostat_operating_mode();
    subscribe(NULL, sub.c_str());
    sub = cfg->get_room_thermostat_hysteresis();
    subscribe(NULL, sub.c_str());
}

void Mqtt_Client::unregister_subs()
{
    std::cout<< date() <<"unregister_subs1"<<std::endl;
    std::string sub = cfg->get_mqtt_Substring();
    std::cout<< date() <<"unregister_subs2"<<std::endl;
    unsubscribe(NULL, sub.c_str());
}

void Mqtt_Client::on_error() {
    std::cout<< date() <<"onerror"<<std::endl;
    return;
    }


void Mqtt_Client::on_connect(int rc)
{
    if (!rc)
    {
        std::cout << date() << "Connected with code " << rc << std::endl;
        // unregister_subs();
        register_subs();
    }
    
}


void Mqtt_Client::on_disconnect(int rc){
    if (!rc){
        std::cout << date() << "disconnected - code " << rc << std::endl;
    }
}

void Mqtt_Client::on_unsubscribe(int mid){
        std::cout<< date()  << "Subscription succeeded. " << " mid: " << mid <<  std::endl;
}


void Mqtt_Client::on_subscribe(int mid, int qos_count, const int *granted_qos){

        std::cout<< date()  << "Subscription succeeded. " << " mid: " << mid << " qos_count: "<< qos_count << " qos_granted: "<< granted_qos << std::endl;
}


void Mqtt_Client::register_config(Config_manager *cfg_){
    cfg = cfg_;
}
 
void Mqtt_Client::register_econet(EcoNet *econet_){
    econet = econet_;
}

void Mqtt_Client::pub_door_state(std::string msg){
    std::string pub = cfg->get_mqtt_Pubstring();
    publish(NULL, pub.c_str(), msg.length(), msg.c_str());
}


void Mqtt_Client::on_message(const struct mosquitto_message *message){
    std::string message_topic(message->topic);
    std::string message_payload(static_cast<char*>(message->payload));
    
    std::cout << date() <<"get instruction: " << message_payload << std::endl;
    

    if(!message_payload.empty() && message_topic == cfg->get_huw_temp())
    {   
        econet->set_huw_temp(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }

    if(!message_payload.empty() && message_topic == cfg->get_huw_pump_mode())
    {   
        econet->set_huw_pump_mode(message_payload.data());
    }

    if(!message_payload.empty() && message_topic == cfg->get_huw_temp_hysteresis())
    {   
        econet->set_huw_temp_hysteresis(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_huw_container_disinfection())
    {   
        econet->set_huw_container_disinfection(static_cast<bool>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_temp())
    {   
        econet->set_boiler_temp(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_on_off())
    {   
        econet->set_boiler_on_off(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_max_power_kw())
    {   
        econet->set_boiler_max_power_kw(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_mid_power_kw())
    {   
        econet->set_boiler_mid_power_kw(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_min_power_kw())
    {   
        econet->set_boiler_min_power_kw(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_max_power_fan())
    {   
        econet->set_boiler_max_power_fan(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_mid_power_fan())
    {   
        econet->set_boiler_mid_power_fan(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_boiler_min_power_fan())
    {   
        econet->set_boiler_min_power_fan(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_mixer_temp())
    {   
        econet->set_mixer_temp(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }
    if(!message_payload.empty() && message_topic == cfg->get_room_thermostat_summer_winter_mode())
    {   
        econet->set_room_thermostat_summer_winter_mode(message_payload.data());
    }
    if(!message_payload.empty() && message_topic == cfg->get_room_thermostat_night_temp())
    {   
        econet->set_room_thermostat_night_temp(std::stof(message_payload.data()));
    }
    if(!message_payload.empty() && message_topic == cfg->get_room_thermostat_day_temp())
    {   
        econet->set_room_thermostat_day_temp(std::stof(message_payload.data()));
    }
    if(!message_payload.empty() && message_topic == cfg->get_room_thermostat_operating_mode())
    {   
        econet->set_room_thermostat_operating_mode(message_payload.data());
    }
    if(!message_payload.empty() && message_topic == cfg->get_room_thermostat_hysteresis())
    {   
        econet->set_room_thermostat_hysteresis(static_cast<uint8_t>(std::stoi(message_payload.data())));
    }

         
 
}

