#include "drive.hpp"

Adafruit_MCP4728 mcp;
error_out DAC_ERROR {error: "Dac error occured", code: {500, 500}};

Drive::Drive(){
    if(!Wire.begin(DAC_SDA_PIN, DAC_SCL_PIN)){
        Drive::out->error(&DAC_ERROR);
    }

    if (!mcp.begin()){
        Drive::out->error(&DAC_ERROR);
    }
}

void Drive::Speed(float left, float right){
    mcp.setChannelValue(MCP4728_CHANNEL_B, map(left ,-1, 1, 0, 4095));
    mcp.setChannelValue(MCP4728_CHANNEL_C, map(right ,-1, 1, 0, 4095));
}