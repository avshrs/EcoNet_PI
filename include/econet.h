#pragma once
#include <string>
#include "vars.h"
#include "USB_serial.h"

class EcoNet{
    public:
        TX_Buffer tx_buf;
        RX_Buffer rx_buf;
        USB_serial serial;
        void init(std::string serialName, int boudrate, int lead_zero);
        void run();

    private:
        void print_buffer(uint8_t *buf, int len);
        std::string date();


};