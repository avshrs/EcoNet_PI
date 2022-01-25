#include <iostream>
#include "econet.h"
#include "Config_manager.h"
#include <thread>
#include "Mosquitto.h"

void th1(EcoNet *econet){
   econet->run();    
}

void th2(Mqtt_Client *mqtt){
    mqtt->client_loop_forever();
}

int main()
{
    Config_manager cfg;
    cfg.read_config();
    
    EcoNet econet;
    std::string serial_file_name = cfg.get_eco_serial_file();
    int rs_lead_zero = cfg.get_eco_lead_zeros();
    int boudrate = cfg.get_eco_boudrate();
    econet.init(serial_file_name.c_str(), boudrate, rs_lead_zero);
    sleep(1);    
    Mqtt_Client mqtt(cfg.get_mqtt_ClientId().c_str(), cfg.get_mqtt_ip().c_str(), cfg.get_mqtt_port(), cfg.get_mqtt_username().c_str(), cfg.get_mqtt_password().c_str());
    mqtt.register_config(&cfg);
    mqtt.register_econet(&econet);
    sleep(1);

    std::thread Mqtt_service(th2, &mqtt);
    std::thread EcoNet_service(th1, &econet);
    
    std::string kmsg = cfg.get_mqtt_keepAliveMsg();
    std::string ktop = cfg.get_mqtt_keepAliveTopic();
    std::string pub ;
    std::string val ;
    
    while (true)
    {
        pub = cfg.sub_get_operating_status();    
        val = econet.get_operating_status();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_huw_temp();    
        val = std::to_string(econet.get_huw_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_feeder_temp();    
        val = std::to_string(econet.get_feeder_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_temp();    
        val = std::to_string(econet.get_boiler_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_weather_temp();    
        val = std::to_string(econet.get_weather_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_exhaust_temp();    
        val = std::to_string(econet.get_exhaust_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_mixer_temp();    
        val = std::to_string(econet.get_mixer_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_boiler_return_temp();    
        val = std::to_string(econet.get_boiler_return_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_upper_buffer_temp();    
        val = std::to_string(econet.get_upper_buffer_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_lower_buffer_temp();    
        val = std::to_string(econet.get_lower_buffer_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_flame_sensor();    
        val = std::to_string(econet.get_flame_sensor());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_ecoster_home_temp();    
        val = std::to_string(econet.get_ecoster_home_temp());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_ecoster_home_temp_target();    
        val = std::to_string(econet.get_ecoster_home_temp_target());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_huw_temp_target();    
        val = std::to_string(econet.get_huw_temp_target());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_temp_target();    
        val = std::to_string(econet.get_boiler_temp_target());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_mixer_temp_target();    
        val = std::to_string(econet.get_mixer_temp_target());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_fuel_level();    
        val = std::to_string(econet.get_fuel_level());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_fan_out_power();    
        val = std::to_string(econet.get_fan_out_power());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_fan_in_power();    
        val = std::to_string(econet.get_fan_in_power());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_huw_pomp_state();    
        val = std::to_string(econet.get_huw_pomp_state());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_pomp_state();    
        val = std::to_string(econet.get_boiler_pomp_state());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_fuel_stream();    
        val = std::to_string(econet.get_fuel_stream());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_power_kw();    
        val = std::to_string(econet.get_boiler_power_kw());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_power_max_time();    
        val = std::to_string(econet.get_power_max_time());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_power_medium_time();    
        val = std::to_string(econet.get_power_medium_time());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_power_min_time();    
        val = std::to_string(econet.get_power_min_time());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_feeder_time();    
        val = std::to_string(econet.get_feeder_time());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_ignitions();    
        val = std::to_string(econet.get_ignitions());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_ignitions_fails();    
        val = std::to_string(econet.get_ignitions_fails());
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_huw_pump_mode();    
       val = econet.get_huw_pump_mode();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_huw_temp_hysteresis();    
        val = econet.get_huw_temp_hysteresis();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_huw_container_disinfection();    
        val = econet.get_huw_container_disinfection();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_on_off();    
        val = econet.get_boiler_on_off();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_max_power_kw();    
        val = econet.get_boiler_max_power_kw();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_mid_power_kw();    
        val = econet.get_boiler_mid_power_kw();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_min_power_kw();    
        val = econet.get_boiler_min_power_kw();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_max_power_fan();    
        val = econet.get_boiler_max_power_fan();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());

        pub = cfg.sub_get_boiler_mid_power_fan();    
        val = econet.get_boiler_mid_power_fan();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_boiler_min_power_fan();    
        val = econet.get_boiler_min_power_fan();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_room_thermostat_summer_winter_mode();    
        val = econet.get_room_thermostat_summer_winter_mode();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_room_thermostat_night_temp();    
        val = econet.get_room_thermostat_night_temp();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_room_thermostat_day_temp();    
        val = econet.get_room_thermostat_day_temp();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_room_thermostat_operating_mode();    
        val = econet.get_room_thermostat_operating_mode();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        pub = cfg.sub_get_room_thermostat_hysteresis();    
        val = econet.get_room_thermostat_hysteresis();
        mqtt.publish(NULL, pub.c_str(), val.length(), val.c_str());
        
        mqtt.publish(NULL, ktop.c_str(), kmsg.length(), kmsg.c_str());
        sleep(60);   
    }
    



return 1;
}


