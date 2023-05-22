#include "power.hpp"

Power::Power(){
    pinMode(VOLTAGE_PIN, INPUT);
}

float Power::Read(){
    int raw_voltage = analogRead(VOLTAGE_PIN);
    float cal_voltage = (float) raw_voltage * 0.00322265625f * 11;
    return cal_voltage;
}