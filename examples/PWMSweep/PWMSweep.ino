/**
 * This test is useful to test the precision of the PWM freqeuncy.
 * You need an oscilloscope or a digital pulse counter to observe the results.
 */
#include <motor_controller.h>
#include <Wire.h>

MotorController mc(0x30);

const int maxSpeed = 100;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - PWM Sweep");
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

  // Duty cycle of 50%
  mc.getFirst().setSpeed(50);

  for(int i = 0; i < 5; i++) {
    mc.setPwmFrequency(1000);
    delay(2000);
    mc.setPwmFrequency(2000);
    delay(2000);
  }
}

void motorSweepPwmFreqeuncyUp() {
  for(int i = 0; i <= 31250; i++) {
    mc.setPwmFrequency(i);
    delay(200);
  }
}

void loop() {
  motorSweepPwmFreqeuncyUp();
}
