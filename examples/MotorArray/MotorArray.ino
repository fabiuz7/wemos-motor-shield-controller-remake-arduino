/**
 * How to create array (or other data structure) of motors.
 */

#include <motor_controller.h>
#include <Wire.h>

MotorController mc1(0x2F);
MotorController mc2(0x30);

// You need to use std::reference_wrapper<Motor> to create a data structures such as vectors.
std::vector<std::reference_wrapper<Motor>> motors;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - Array of Motors");
  Serial.println();
  
  Wire.begin();

  Serial.print("Motor controller initialization... ");
  bool result1 = mc1.begin();
  bool result2 = mc2.begin();
  if(result1 && result2) {
    Serial.println("Done!");
  } else {
    Serial.println("Error!");
    while(1) { 
      delay(1000);
    }
  }
  
  motors.push_back(mc1.getFirst());
  motors.push_back(mc1.getSecond());
  motors.push_back(mc2.getFirst());
  motors.push_back(mc2.getSecond());

  // Method 1
  // Traditional for(;;), note the declaration Motor&
  for (int i = 0 ; i < motors.size(); i++) {
    Motor& m = motors[i];
    m.setSpeed(100);
  }

  // Method 2
  // New simplified for(:), also note the declaration of Motor&
  for(Motor& m : motors) {
    m.setSpeed(100);
  }

  // Method 3
  // Last way to iterate over an array of motor. Notice the mandatory use
  // of get() method
  for (int i = 0 ; i < motors.size(); i++) {
    motors[i].get().setSpeed(100);
  }
}

void loop() {
  for(Motor& m : motors) {
    m.setSpeed(100);
  }
  delay(2000);

  for(Motor& m : motors) {
    m.setSpeed(0);
  }
  delay(2000);
}
