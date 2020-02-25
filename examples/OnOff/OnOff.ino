#include <motor_controller.h>
#include <Wire.h>

MotorController mc(0x30);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - On/Off");
  Serial.println();
  
  Wire.begin();

  Serial.print("Motor Controller initialization... ");
  bool result = mc.begin();
  if(result) {
    Serial.println("Done!");
  } else {
    Serial.println("Error!");
    while(1) { 
      delay(1000); 
    }
  }
}

void loop() {
  Serial.print("Loop... ");
  Motor& motor = mc.getFirst();
  motor.setSpeedDirection(100, Motor::Direction::CW);
  delay(1000);
  
  motor.stop();
  delay(2000);
  
  motor.setSpeedDirection(100, Motor::Direction::CCW);
  delay(1000);
  
  motor.stop();
  Serial.println("Finished!");

  delay(3000);
}
