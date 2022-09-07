#include <MPU6050_tockn.h>
MPU6050 mpu6050(Wire);

typedef struct {
  double Xangle;
  double Yangle;
  double Zangle;
  double temperature;
  double rate;
  long duration;    // us
  long timer;
  double last_z_angle;
  double gyro_drift_compensation;
  double mpuZangle;
} MPU;

MPU mpu{0,0,0,0,100,0,0,0,0,0};

// calculate gyro offsets
bool calibrate_gyro_offsets = false;


void MPU6050_setup(int rate=100) {
  mpu6050.begin();

  if (calibrate_gyro_offsets) {
    mpu6050.calcGyroOffsets(true);
    delay(5000);
    mpu6050.calcGyroOffsets(true);
    delay(5000);
    mpu6050.calcGyroOffsets(true);
    delay(5000);    
    while(1);
  }
  
  mpu6050.setGyroOffsets(-4.65,2.34,-0.28);
  mpu.rate = rate;
  mpu.duration = 1000000.0 / mpu.rate;
}


void MPU6050_run() {
  mpu6050.update();

  if((currenttime - mpu.timer) >= mpu.duration){
    mpu.Xangle = mpu6050.getAngleX();
    mpu.Yangle = mpu6050.getAngleY();
    mpu.mpuZangle = mpu6050.getAngleZ();
    mpu.temperature = mpu6050.getTemp();

    mpu.timer = currenttime;

    mpu.Zangle += (mpu.mpuZangle - mpu.last_z_angle) + mpu.gyro_drift_compensation;  // correct for gyro drift about z axis
    // Serial.print(mpu.Zangle); Serial.print("\t"); Serial.print(steer.input); Serial.print("\t"); Serial.println(control.gyro_drift_compensation);
    mpu.last_z_angle = mpu.mpuZangle;
  
    // // for debugging purposes
    // Serial.print("X angle: ");
    // Serial.print(mpu.Xangle);
    // Serial.print("\tY angle: ");
    // Serial.print(mpu.Yangle);
    // Serial.print("\tZ angle: ");
    // Serial.print(mpu.Zangle);
    // Serial.println();
    
  }

}