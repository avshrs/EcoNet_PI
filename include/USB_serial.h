#pragma once
#include <stdint.h>
#include <string>
#include "vars.h"
#include <vector>
class USB_serial
{
  public:
    int fd;
    int lead_z = 0 ;
    void serial_open(const char* serial_name, int boudrate, int lead_zero );
    void serial_send(std::vector<uint8_t> &tx_buffer);
    void serial_read_buffer(RX_Buffer &rx_buffer);
    void serial_read_byte(std::vector<uint8_t> &vect);
    void serial_read_bytes(std::vector<uint8_t> &vect, int len);
    void clear_buffer();
    void send_brake();

    uint8_t serial_read_byte(char *data, int timeout_usec);
    void serial_close();
    int convert_baudrate(unsigned int baudrate);
    


};


