#include "out.hpp"

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Out::Out(){
    pixels.begin();
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);
}

void Out::error(error_out *error){
    // Log error
    if(node_handler != nullptr){ node_handler->logerror(error->error.c_str());}
    
    for (;;){
        for (size_t i = 0; i < 4; i++)
        {
            if(i == 0 || i == 2){
                pixels.setPixelColor(PIXELINDEX,  pixels.Color(150, 0, 0));
                pixels.show();
                digitalWrite(BUZZER_PIN, LOW);
                delay(error->code[i]);
            } else {
                pixels.setPixelColor(PIXELINDEX,  pixels.Color(0, 0, 0));
                pixels.show();
                digitalWrite(BUZZER_PIN, HIGH);
                delay(error->code[i]);
            }
        }
    }
}

void Out::info(info_out *info){
    // Log info
    if(node_handler != nullptr){ node_handler->logerror(info->info.c_str());}
}

void Out::color(color_out *color){
    pixels.setPixelColor(0,  pixels.Color(color->r, color->g, color->b));
    pixels.show();
}