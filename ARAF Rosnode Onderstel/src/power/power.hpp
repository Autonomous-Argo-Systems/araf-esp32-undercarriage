#ifndef POWER_HPP
#define POWER_HPP
#include <Arduino.h>

#define VOLTAGE_PIN 4
#define RELAY_PIN 16
#define ENABLE_PIN 17

class Power
{
public:
    /// @brief Boots up power hardware
    Power();

    /// @brief Reads battery voltage
    /// @return The value as float
    float Read();

    /// @brief Switches relay on the board
    /// @param state on or of as true or false
    void Switch(bool state);
};

#endif