#ifndef OUT_HPP
#define OUT_HPP

#include <ros.h>
#include <Adafruit_NeoPixel.h>

typedef struct {
    String error;
} error_out;

typedef struct {
    String info;
} info_out;

typedef struct {
    int r; int g; int b;
} color_out;

// Out IO
#define NEOPIXEL_PIN 15
#define NUMPIXELS 1
#define PIXELINDEX 0
#define BUZZER_PIN 2

class Out
{
public:
    /// @brief internal variables
    ros::NodeHandle *node_handler;
    color_out active;

    /// @brief setup the out channel
    /// @param node_handler 
    Out();

    /// @brief log an error message
    /// @param error 
    void error(error_out error);

    /// @brief log an info message
    /// @param info 
    void info(info_out info);

    /// @brief set an log color
    /// @param color 
    void color(color_out color);

    /// @brief beep for a certain time
    /// @param wait 
    void beep(int wait);
};

#endif
