#include "power.hpp"
#define DIVIDED_CONSTANT 0.0008056640625f
#define MULTIPLY_CONSTANT 11.0f

Power::Power(){
    pinMode(VOLTAGE_PIN, INPUT);
}

float Power::Read(){
    int raw_voltage = analogRead(VOLTAGE_PIN);
    float cal_voltage = (float) raw_voltage * DIVIDED_CONSTANT * MULTIPLY_CONSTANT;
    return cal_voltage;
}