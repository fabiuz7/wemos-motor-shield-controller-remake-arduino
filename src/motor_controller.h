#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "motor.h"
#include <functional>

/**
 * This class represents a Wemos Motor Shield.
 * Each controller includes two Motors.
 *
 * The usage of std::reference_wrapper allow to use references
 * instead of pointer and allow to store references and structures
 * such as vector.
 */
class MotorController {
public:
  MotorController(uint8_t i2cAddress, uint8_t resetPin = UNDEFINED_PIN, uint8_t standbyPin = UNDEFINED_PIN);

  /**
   * Call this to initialize the shield. The shield will be enabled.
   * Return true if the shield if connected.
   */
  bool begin();
  
  /**
   * Get the first instance of motor.
   */
  std::reference_wrapper<Motor> getFirst();

  /**
   * Get the first instance of motor.
   */
  std::reference_wrapper<Motor> getSecond();

  /**
   * Enable the power domain of the shield, necessary to control the motors.
   */
  void enable();

  /**
   * Disable the power domain of the shield, it goes in standby mode (or low power mode).
   * Commands received when the controller is disabled are not delivered.
   */
  void disable();

  /**
   * Return true if active, false if standby.
   */
  bool isEnabled() const;

  /**
   * Hard reset for the shield. After the reset, you have to call begin().
   */
  void reset();

  /**
   * Resend the last command sent to the shield.
   */
  void forceUpdate();

  /**
   * Set PWM frequency delivered to the motors. Max supported 
   * frequency by this shield is 31250Hz, higher values are cut to this values.
   * if zero it hasn't any effect.
   */
  void setPwmFrequency(uint32_t frequency);

  const static uint8_t UNDEFINED_PIN = 255;

private:
  enum MotorMode { SHORT_BRAKE = 0, CCW = 1, CW = 2, STOP = 3, STANDBY = 4};

  const static uint8_t MOTOR_CONTROLLER_DEBUG = 0;

  uint8_t i2cAddress;
  uint8_t resetPin;
  uint8_t standbyPin;

  bool active; 
  const static uint32_t maxPwmFrequency = 31250;
  uint32_t pwmFrequency;  
  uint32_t lastCommand;
  
  Motor motorA;
  Motor motorB;

  /**
   * Change the state of a motor (manage brake, ccw, cw and stop, but not standby).
   */
  void setMotor(Motor* motor, MotorMode mode, uint8_t speed);

  /**
   * Every I2C command is sent through this function.
   */
  uint8_t sendCommand(uint32_t command);

  friend class Motor;
};

#endif // END MOTOR_CONTROLLER_H
