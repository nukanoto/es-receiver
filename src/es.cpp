#include "es.h"

ES920LR3::ES920LR3(int rx_pin, int tx_pin) : _rx_pin(rx_pin), _tx_pin(tx_pin), _initialized(false)
{
}

bool ES920LR3::init()
{
    if (!enter_config_mode())
    {
        return false;
    }

    if (!configure_module())
    {
        return false;
    }

    _initialized = true;
    return true;
}

void ES920LR3::reset()
{
    Serial2.end();
    pinMode(_rx_pin, OUTPUT);
    pinMode(_tx_pin, OUTPUT);
    digitalWrite(_rx_pin, LOW);
    digitalWrite(_tx_pin, LOW);
    delay(1000);
    pinMode(_rx_pin, INPUT);
    pinMode(_tx_pin, INPUT);
}

bool ES920LR3::enter_config_mode()
{
    String rx;

    while (1)
    {
        reset();
        Serial2.begin(115200, SERIAL_8N1, _rx_pin, _tx_pin);
        Serial2.setTimeout(50);
        delay(50);
        rx = Serial2.readString();
        if (rx.indexOf("Select Mode") >= 0)
            break;
        send_command("config");
    }
    return true;
}

bool ES920LR3::send_command(String command)
{
    String rx;
    Serial2.print(command);
    Serial2.print("\r\n");
    Serial2.flush();
    delay(10);
    rx = Serial2.readString();
    Serial.print(rx);
    return (rx.indexOf("OK") >= 0);
}

bool ES920LR3::configure_module()
{
    if (!send_command("2")) // processor mode
        return false;
    if (!send_command("x")) // default
        return false;
    if (!send_command("c 12")) // spread factor
        return false;
    if (!send_command("d 3")) // channel
        return false;
    if (!send_command("e 2345")) // PAN ID
        return false;
    if (!send_command("f 0")) // own ID
        return false;
    if (!send_command("g ffff")) // broadcast
        return false;
    if (!send_command("p 1")) // RSSI on
        return false;
    if (!send_command("z")) // start
        return false;
    return true;
}

bool ES920LR3::send_data(String data)
{
    if (!_initialized)
        return false;

    Serial2.print(data);
    Serial2.print("\r\n");
    Serial2.flush();
    return true;
}

String ES920LR3::receive_data()
{
    if (!_initialized)
        return "";

    if (Serial2.available())
    {
        return Serial2.readString();
    }
    return "";
}

bool ES920LR3::is_available()
{
    if (!_initialized)
        return false;
    return Serial2.available();
}