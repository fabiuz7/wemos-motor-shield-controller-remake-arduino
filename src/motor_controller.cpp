#include "motor_controller.h"
#include <Wire.h>
#include <Arduino.h>

bool MotorController::begin(){
  // Make sure to exit from hardware reset mode
  if(resetPin != UNDEFINED_PIN) {
    pinMode(resetPin, OUTPUT);
    // Reset is active low
    digitalWrite(resetPin, HIGH);
  }

  if(standbyPin != UNDEFINED_PIN) {
    pinMode(standbyPin, OUTPUT);
  }

  enable();

  // Check the command result to verify if the shield is reachable
  uint32_t command = pwmFrequency & 0x0fffffff;
  uint8_t error = sendCommand(command);
  if(!error) {
    return true;
  }
  return false;
}

std::reference_wrapper<Motor> MotorController::getFirst() {
  return motorA;
}

std::reference_wrapper<Motor> MotorController::getSecond() {
  return motorB;
}

void MotorController::disable() {
  if(standbyPin != UNDEFINED_PIN) {
    digitalWrite(standbyPin, LOW);
  } else {
    uint32_t command = 0x10 << 24;
    command |= (STANDBY << 16);
    sendCommand(command);
  }
  active = false;
}

void MotorController::enable() {
  if(standbyPin != UNDEFINED_PIN) {
    digitalWrite(standbyPin, HIGH);
  }
  active = true;
}

bool MotorController::isEnabled() const {
  return active;
}

void MotorController::setPwmFrequency(uint32_t frequency) {
  if(!active) {
    return;
  }

  if(frequency > 100000) {
    frequency = 100000;
  }
  if(frequency == 0) {
    return ;
  }
  pwmFrequency = frequency;

  sendCommand(pwmFrequency & 0x0fffffff);
}

void MotorController::reset() {
  if(resetPin != UNDEFINED_PIN) {
    if(MOTOR_CONTROLLER_DEBUG) Serial.println("[MOTOR CONTROLLER] resetting");
    digitalWrite(resetPin, LOW);
    delay(5);
    digitalWrite(resetPin, HIGH);
    delay(10);
  } else {
    if(MOTOR_CONTROLLER_DEBUG) Serial.println("[MOTOR CONTROLLER] You have to set the reset pin");
  }
}

void MotorController::forceUpdate() {
  sendCommand(lastCommand);
}

MotorController::MotorController(uint8_t i2cAddress, uint8_t resetPin, uint8_t standbyPin):
      i2cAddress(i2cAddress),
      resetPin(resetPin), standbyPin(standbyPin), active(false),
      pwmFrequency(1000), lastCommand(0), motorA(this), motorB(this) {
}

void MotorController::setMotor(Motor* motor, MotorMode mode, uint8_t speed) {
  if(!active) {
    return;
  }

  if(mode == MotorMode::STANDBY) {
    return;
  }

  uint8_t motorId = 0;
  if(motor == &motorA) {
    motorId = 0;
  } else if(motor == &motorB) {
    motorId = 1;
  } else {
    if(MOTOR_CONTROLLER_DEBUG) Serial.println("[MOTOR CONTROLLER] Fatal Error, wrong motor pointer!");
  }
  
  uint16_t realSpeed = speed * 100;
  if(realSpeed > 10000){
    realSpeed = 10000;
  }

  uint32_t command = 0;
  command |= (motorId | 0x10) << 24;
  command |= mode << 16;
  command |= realSpeed;
  sendCommand(command);
}

uint8_t MotorController::sendCommand(uint32_t command){
  if(MOTOR_CONTROLLER_DEBUG){
    Serial.print("[MOTOR CONTROLLER] Sending command: ");
    Serial.print((uint8_t)(command>>24), HEX); Serial.print(" ");
    Serial.print((uint8_t)(command>>16), HEX); Serial.print(" ");
    Serial.print((uint8_t)(command>>8), HEX); Serial.print(" ");
    Serial.println((uint8_t)command, HEX);
  }
  Wire.beginTransmission(i2cAddress);
  Wire.write(command >> 24);
  Wire.write(command >> 16);
  Wire.write(command >> 8);
  Wire.write(command);
  lastCommand = command;
  return Wire.endTransmission();
}
