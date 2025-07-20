#pragma once
#include <Arduino.h>

class ES920LR3
{
public:
    ES920LR3(int rx_pin = 16, int tx_pin = 15);

    bool init();
    bool send_command(String command);
    bool send_data(String data);
    String receive_data();
    bool is_available();

private:
    int _rx_pin;
    int _tx_pin;
    bool _initialized;

    void reset();
    bool enter_config_mode();
    bool configure_module();
};