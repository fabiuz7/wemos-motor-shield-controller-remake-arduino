#include "motor.h"
#include "motor_controller.h"

Motor::Direction Motor::getDirection() {
  return direction;
}

void Motor::setDirection(Motor::Direction direction) {
  if(motorController == nullptr) {
    return;
  }

  this->direction = direction;
  if(speed != 0){
      executeMovementCommand();
  }
}

void Motor::toggleDirection() {
  if(motorController == nullptr) {
    return;
  }

  if(direction == Direction::CW) {
    direction = Direction::CCW;
  } else {
    direction = Direction::CW;
  }

  if(speed != 0){
      executeMovementCommand();
  }
}

uint8_t Motor::getSpeed() const {
  return speed;
}

void Motor::setSpeed(uint8_t speed) {
  if(motorController == nullptr) {
    return;
  }

  if(speed > 100) {
    speed = 100;
  }
  this->speed = speed;

  executeMovementCommand();
}

void Motor::setSpeedDirection(uint8_t speed, Direction direction){
  if(motorController == nullptr) {
    return;
  }

  if(speed > 100) {
    speed = 100;
  }
  this->speed = speed;
  this->direction = direction;

  executeMovementCommand();
}

void Motor::stop() {
  if(motorController == nullptr) {
    return;
  }

  speed = 0;
  braked = false;
  motorController->setMotor(this, MotorController::STOP, 0);
}

bool Motor::isBraked() const {
  return speed == 0 && braked;
}

void Motor::brake() {
  if(motorController == nullptr) {
    return;
  }

  speed = 0;
  motorController->setMotor(this, MotorController::SHORT_BRAKE, 0);
}

Motor::Motor(MotorController* mc): motorController(mc) {};

void Motor::executeMovementCommand() {
  if(direction == Direction::CW) {
    motorController->setMotor(this, MotorController::CW, speed);
  }else{
    motorController->setMotor(this, MotorController::CCW, speed);
  }
}
