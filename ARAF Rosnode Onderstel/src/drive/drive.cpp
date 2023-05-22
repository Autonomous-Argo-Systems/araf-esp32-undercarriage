#include "drive.hpp"
#include <math.h>

// Dac used for pwm
Adafruit_MCP4728 mcp;

// PWM variables
int left_delay;
int right_delay;
int delay_passed;
const int delay_cycle = 1000;
const int delay_offset = 50;
const int delay_cap = 50;
TaskHandle_t pwm_handle;

void PWMTask( void * parameter) {
  for(;;) {
    // Setting pulse high
    if ( left_delay != 0) {
        mcp.setChannelValue(MCP4728_CHANNEL_C, 4095);
    }

    if (right_delay != 0) {
        mcp.setChannelValue(MCP4728_CHANNEL_B, 4095);
    }

    // Awaiting 
    delay_passed = left_delay < right_delay ? left_delay : right_delay;
    delayMicroseconds(delay_passed);

    // Setting pulse low
    MCP4728_channel_t channel = left_delay < right_delay ?  MCP4728_CHANNEL_C : MCP4728_CHANNEL_B;
    mcp.setChannelValue(channel, 0);
    int delay = abs(left_delay - right_delay);
    delay_passed += delay;
    delayMicroseconds(delay);
    channel = left_delay > right_delay ?  MCP4728_CHANNEL_B : MCP4728_CHANNEL_C;
    mcp.setChannelValue(channel, 0);

    // Awaiting
    delayMicroseconds(delay_cycle - delay_passed);
  }
}

Drive::Drive(){
    // Setting correct i2c settins
    if(!Wire.begin(DAC_SDA_PIN, DAC_SCL_PIN, DAC_I2C_FREQ)){
        Drive::out->error({error: "Dac error occured"});
    }

    // Starting dac.
    if (!mcp.begin()){
        Drive::out->error({error: "Dac error occured"});
    }

    // Starting pwm thread
    xTaskCreatePinnedToCore(
      PWMTask,
      "TaskPWM",
      10000, 
      NULL, 
      0, 
      &pwm_handle, 
      1);

    // Starting motordrivers
    left_delay = 600;
    right_delay = 600;
    delay(4000);
    left_delay = 0;
    right_delay = 0;
}


void Drive::Speed(float left, float right){
    if (left > -0.1f && left < 0.1f){
        left_delay = 0;
    } else {
        left_delay = delay_offset + ((left + 1.0f) / 2.0f) * (delay_cycle - delay_cap);
    }

    if (right > -0.1f && right < 0.1f){
        right_delay = 0;
    } else {
        right_delay = delay_offset + ((right + 1.0f)/ 2.0f) *  (delay_cycle - delay_cap);;
    }
}