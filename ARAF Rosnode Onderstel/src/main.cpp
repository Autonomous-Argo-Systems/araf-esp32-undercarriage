#include <Arduino.h>
#include "out/out.hpp"
#include "power/power.hpp"
#include "drive/drive.hpp"
#include <sensor_msgs/BatteryState.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <time.h>

// Setting ros timeout
#define ROS_START_TIMEOUT 200
#define ROS_LOST_TIMEOUT 10
time_t previous_seconds;
bool previously_connected = false;

// Data.
Out *out;
Power *power;
Drive *drive;

// Functions
void driving(const geometry_msgs::Twist &twist){
  drive->Speed(twist.linear.x, twist.linear.y);
  info_out info = {info: "Got a driving message."};
  out->info(&info);
}

void powering(const std_msgs::Bool &state){
  power->Switch(state.data);
  info_out info = {info: "Got a power message."};
  out->info(&info);
}

// Ros.
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub_drive("cmd_vel", &driving);
ros::Subscriber<std_msgs::Bool> sub_power("switch", &powering);
sensor_msgs::BatteryState battery_msg;
ros::Publisher pub_battery("battery", &battery_msg);
error_out ROS_ERROR {error: "", code: {1000, 0}}; // Cannot log this error so no error message.

void setup() {
  // Starting up logging.
  out = new Out();
  color_out boot = {r: 150, g: 150, b:150};
  out->color(&boot);

  // Starting up ros.
  nh.initNode();
  out->node_handler = &nh;

  // Starting up hardware.
  drive = new Drive();
  power = new Power();

  // Starting up pub and subs.
  nh.subscribe(sub_drive);
  nh.subscribe(sub_power);
  nh.advertise(pub_battery);

  delay(1000);
  previous_seconds = time(NULL);
}

void loop() {
  if (!nh.connected()){
    // Setting no connection status
    color_out boot = {r: 0, g: 0, b: 150};
    out->color(&boot);

    // Going in error state after timeout
    if (!previously_connected && time(NULL) >= (previous_seconds + ROS_START_TIMEOUT)){
      out->error(&ROS_ERROR);
    } else if (previously_connected && time(NULL) >= (previous_seconds + ROS_LOST_TIMEOUT)){
      out->error(&ROS_ERROR);
    }
  } else {
    // Setting connected status
    previously_connected = true;
    previous_seconds = time(NULL);
    color_out running = {r: 0, g: 150, b:0};
    out->color(&running);

    // Measuring and pub battery.
    battery_msg.voltage = power->Read();
    battery_msg.percentage = ((battery_msg.voltage - 23.0f) / 3.0f) * 100.0f;
    pub_battery.publish(&battery_msg);     
  }
  nh.spinOnce();  
}