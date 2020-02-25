#include <motor_controller.h>
#include <Wire.h>

MotorController mc(0x30);

const int maxSpeed = 100;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - Speed Sweep");
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

void motorSweepSpeedUp(Motor& motor) {
  for(int i = 0; i <= maxSpeed; i++) {
    motor.setSpeed(i);
    delay(200);
  }
}

void motorSweepSpeedDown(Motor& motor) {
  for(int i = maxSpeed; i >= 0; i--) {
    motor.setSpeed(i);
    delay(200);
  }
}

void loop() {
  Motor& motor = mc.getFirst();
  Serial.println("Direction CW");
  motor.setDirection(Motor::Direction::CW);
  motorSweepSpeedUp(motor);
  delay(500);
  motorSweepSpeedDown(motor);
  motor.stop();
  delay(1000);

  Serial.println("Direction CCW");
  motor.setDirection(Motor::Direction::CCW);
  motorSweepSpeedUp(motor);
  delay(500);
  motorSweepSpeedDown(motor);
  motor.stop();
  Serial.println("Done!");
  Serial.println();

  delay(2000);
}
