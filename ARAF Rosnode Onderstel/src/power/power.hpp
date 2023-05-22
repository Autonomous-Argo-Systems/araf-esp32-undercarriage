#ifndef POWER_HPP
#define POWER_HPP
#include <Arduino.h>

#define VOLTAGE_PIN 4

class Power
{
public:
    /// @brief Boots up power hardware
    Power();

    /// @brief Reads battery voltage
    /// @return The value as float
    float Read();
};

#endif