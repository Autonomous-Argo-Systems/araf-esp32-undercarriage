#include "drive.hpp"

// Dac used for pwm
Adafruit_MCP4728 mcp;

Drive::Drive(){
    // Setting correct i2c settins
    if(!Wire.begin(DAC_SDA_PIN, DAC_SCL_PIN, DAC_I2C_FREQ)){
        Drive::out->error({error: "Dac error occured"});
    }

    // Starting dac.
    if (!mcp.begin()){
        Drive::out->error({error: "Dac error occured"});
    }

    // Starting motordrivers
    for (size_t i = 0; i < 1000; i++)
    {
      mcp.fastWrite(4095, 4095, 4095, 0);
      delayMicroseconds(600);
      mcp.fastWrite(0, 0, 0, 0);
      delayMicroseconds(400);
    }
}


void Drive::Speed(float left, float right){
    String test;
    if (left > -0.1f && left < 0.1f){
        mcp.setChannelValue(MCP4728_CHANNEL_C, 0);
    } else {
        int left_range = 1000 + (((left + 1.0f) / 2.0f) * 2000);
        mcp.setChannelValue(MCP4728_CHANNEL_C, left_range);
    }

    if (right > -0.1f && right < 0.1f){
        mcp.setChannelValue(MCP4728_CHANNEL_B, 0);
    } else {
        int right_range = 1000 + (((right + 1.0f) / 2.0f) * 2000);
        mcp.setChannelValue(MCP4728_CHANNEL_B, right_range);
    }
}