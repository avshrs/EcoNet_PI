#include <iostream>
#include "econet.h"
#include "Config_manager.h"


int main()
{
    Config_manager cfg;
    cfg.read_config();

    EcoNet econet;
    std::string serial_file_name = cfg.get_eco_serial_file();
    int rs_lead_zero = cfg.get_eco_lead_zeros();
    int boudrate = cfg.get_eco_boudrate();
    econet.init(serial_file_name.c_str(), boudrate, rs_lead_zero);
    



return 1;
}


