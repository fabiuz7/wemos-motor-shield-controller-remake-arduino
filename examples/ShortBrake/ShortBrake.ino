/**********************************************
 * Short brake Example
 * You can see the different effect of stop()
 * and brake() functions attaching 2 motors to
 * the shield.
 **********************************************/
 
#include <motor_controller.h>
#include <Wire.h>

MotorController mc(0x30);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - Short Brake");
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
  Motor& motor1 = mc.getFirst();
  Motor& motor2 = mc.getSecond();

  motor1.setSpeed(100);
  motor2.setSpeed(100);
  delay(800);
  
  motor1.stop();
  motor2.brake();
  delay(800);
}
