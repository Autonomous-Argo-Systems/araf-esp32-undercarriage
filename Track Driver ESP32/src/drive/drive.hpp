#ifndef DRIVING_HPP
#define DRIVING_HPP

#include <Adafruit_MCP4728.h>
#include <Wire.h>
#include "out/out.hpp"

// DAC Settings
#define DAC_SDA_PIN 22
#define DAC_SCL_PIN 21
#define DAC_I2C_FREQ 3400000

class Drive
{
public:
    // bind a out for debugging
    Out *out;

    /// @brief Boots up power hardware
    Drive();

    /// @brief Sets speed
    void Speed(float left, float right);
};

#endif