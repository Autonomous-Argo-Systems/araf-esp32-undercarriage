#ifndef DRIVING_HPP
#define DRIVING_HPP

#include <Adafruit_MCP4728.h>
#include <Wire.h>
#include "out/out.hpp"

// DAC Settings
#define DAC_SDA_PIN 22
#define DAC_SCL_PIN 21

class Drive
{
public:
    Out *out;

    /// @brief Boots up power hardware
    Drive();

    /// @brief Reads battery voltage
    /// @return The value as float
    void Speed(float left, float right);
};

#endif