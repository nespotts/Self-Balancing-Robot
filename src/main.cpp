#include <Arduino.h>

long currenttime = 0;
#include <Wire.h>
#include "MPU_functions.h"
#include "Lidar_scan.h"
#include "Odometry.h"
#include "motor_controls.h"
#include "PID_controls.h"
#include "battery_monitor.h"
#include "NRF_radio.h"
#include "beeper_controller.h"
BalanceBeeper beeper;
#include "control_logic.h"

#include "functions.h"
#include "Plotter.h"
Plotter p;


//====================================================================
// Setup
//====================================================================
void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // wait until serial port opens ... For 5 seconds max
  while (!Serial && millis() < 5000)
    ;

  // left pin, right pin, odom rate (50 max clean), num of avg points
  Odometry_setup(6,7,40,7);
  // servo pin, num subdivisions
  scan_setup(5,16);
  motor_setup();
  Radio_Setup(3);
  MPU6050_setup(400);
  controls_setup();

  battery_setup();
  beeper.setup();

  p.Begin();
  // p.AddTimeGraph("Left Odometry", 10000, "Distance", encoder[0].distance, "Velocity", encoder[0].velocity, "Acceleration", encoder[0].accel);
  // p.AddTimeGraph("Lidar", 10000, "Range 1", sensors[0].range, "Range 2", sensors[1].range);
  // p.AddTimeGraph("Right Odometry", 10000, "Distance", encoder[1].distance, "Velocity", encoder[1].velocity, "Acceleration", encoder[1].accel);
  // p.AddTimeGraph("Odom 2", 10000, "Centroidal Distance", odom.cent_distance, "Centroidal Velocity", odom.cent_velocity, "Centroidal Acceleration", odom.cent_accel);
  // p.AddTimeGraph("Odom 2", 10000, "theta", odom.theta);
  // p.AddXYGraph("Position", 100000, "X", odom.x, "Y", odom.y);
  // p.AddTimeGraph("Debugging", 10000, "distance", encoder[1].distance);
  // p.AddTimeGraph("Loop Frequency", 10000, "Loop Frequency", freq);
  // p.AddTimeGraph("Y angle", 10000, "Y angle", mpu.Yangle, "balance output", bal.output, "target", bal.setpoint);
  p.AddTimeGraph("Encoder Counts", 10000, "left encoder", encoder[0].count, "right encoder", encoder[1].count);
}



long last_count;
long print_timer;
long print_duration = 1000000;


//====================================================================
// loop
//====================================================================
void loop() {
  currenttime = micros();
  p.Plot();
  Odometry_Upate();
  scan_run();
  MPU6050_run();
  controls_run();
  battery_run();
  beeper.loop();
  Receive_Data();
  // Serial.println(scan.ranges[scan.front_index]);
  // Serial.println(sensors[0].range);

  // if ((currenttime - print_timer) >= print_duration) {
  //   Serial.print("Left: "); Serial.print(encoder[0].count-last_count); Serial.print(" counts/s");
  //   Serial.println();
  //   last_count = encoder[0].count;
  //   print_timer = currenttime;
  // }


  // Calc_Loop_Speed();
}










 





  


















