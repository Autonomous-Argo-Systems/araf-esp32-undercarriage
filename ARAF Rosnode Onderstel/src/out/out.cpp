#include "out.hpp"

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Out::Out(){
    pixels.begin();
    pinMode(BUZZER_PIN, OUTPUT);
}

void Out::error(error_out error){
    if(node_handler != nullptr){ node_handler->logerror(error.error.c_str());}
    pixels.setPixelColor(PIXELINDEX,  pixels.Color(150, 0, 0));
    digitalWrite(BUZZER_PIN, HIGH);
    
    // Blocking program for ever!
    for (;;){
        delay(1);
    }
}

void Out::info(info_out info){
    if(node_handler != nullptr){ node_handler->logerror(info.info.c_str());}
}

void Out::color(color_out color){
    pixels.setPixelColor(0,  pixels.Color(color.r, color.g, color.b));
    pixels.show();
}

void Out::beep(int wait){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(wait);
    digitalWrite(BUZZER_PIN, LOW);
}