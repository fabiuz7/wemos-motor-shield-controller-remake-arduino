/**
 * Sketch to test the standy mode (low power mode). 
 * 
 * You will need a multimeter to check the real benefit of standby mode
 * (low power mode). When disabled, the module will consume 2mA (Icc) less.
 * 
 * NOTE: you have to join the solder pad on IO Standby.
 */
#include <motor_controller.h>
#include <Wire.h>

// Sketch for Wemos/Lolin D1, Connect the standby pin (S) to D6.
MotorController mc(0x30, MotorController::UNDEFINED_PIN, D6);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println("Wemos Motor Shield Remake - Enable/Disable IO");
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
  mc.disable();
  Serial.println("Motor disabled");
  delay(2000);

  // Now the shield is ready to receive command
  mc.enable();
  
  Motor& m = mc.getFirst();
  m.setSpeed(50);
  Serial.println("Motor running");
  delay(2000);

  m.stop();
  Serial.println("Motor stopped");
  delay(2000);

  Serial.println();
}
