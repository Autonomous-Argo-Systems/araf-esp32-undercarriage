#include <Arduino.h>
#include "out/out.hpp"
#include "power/power.hpp"
#include "drive/drive.hpp"
#include <sensor_msgs/BatteryState.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <time.h>

// Data.
Out *out;
Power *power;
Drive *drive;

// Driving.
void driving(const geometry_msgs::Twist &twist){
  drive->Speed(twist.linear.x, twist.linear.y);
  out->info({info: "Got a driving message."});
}

// Ros.
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub_drive("cmd_vel", &driving);
sensor_msgs::BatteryState battery_msg;
ros::Publisher pub_battery("battery", &battery_msg);

void setup() {
  // Starting up logging.
  out = new Out();
  out->color({r: 150, g: 150, b:150});

  // Starting up ros.
  nh.initNode();
  out->node_handler = &nh;

  // Starting up hardware.
  drive = new Drive();
  power = new Power();

  // Starting up pub and subs.
  nh.subscribe(sub_drive);
  nh.advertise(pub_battery);
}

void loop() {
  if (!nh.connected()){
    out->color({r: 0, g: 0, b: 150});
  } else {
    out->color({r: 0, g: 150, b:0});

    battery_msg.voltage = power->Read();
    battery_msg.percentage = ((battery_msg.voltage - 23.0f) / 3.0f) * 100.0f;
    pub_battery.publish(&battery_msg);     
  }
  nh.spinOnce();  
}