#include "power.hpp"

Power::Power(){
    pinMode(VOLTAGE_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
}

float Power::Read(){
    return analogRead(VOLTAGE_PIN);
}

void Power::Switch(bool state){
    if (state){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(ENABLE_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(ENABLE_PIN, LOW);
    }
}