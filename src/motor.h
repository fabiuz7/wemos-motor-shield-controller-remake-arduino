#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

class MotorController;

/**
 * This class represents a single motor.
 */
class Motor {
public:
  enum class Direction {CW, CCW};

  /**
   * Default constructor, motors initialized with it cannot communicate
   * with the controller.
   */
  Motor(): motorController(nullptr) {};
  Motor(const Motor&) = delete;
  Motor& operator=(const Motor&) = delete;

  /**
   * Get the motor direction. It hasn't any effect until start()
   * is called. Not meaningful if motor is stopped. 
   */;
  Direction getDirection();

  /**
   * Set direction. 
   * NOTE: that if motor is stop this call has no (immediate) effect.
   */
  void setDirection(Direction direction);

  /**
   * Toggle the direction. 
   * NOTE: that if motor is stop this call has no (immediate) effect.
   */
  void toggleDirection();

  /**
   * Get the motor speed, values between [0; 100].
   * Speed 0 means that the motor was stop or short braked.
   * Use isShortBraked() to distinguish between the 2 cases.
   */
  uint8_t getSpeed() const;
  
  /**
   * Set the motor speed. Values between [0; 100].
   * NOTE: speed = 0 is equal to call stop().
   */
  void setSpeed(uint8_t speed);

  /**
   * Start motor with the previously specified speed and direction.
   * NOTE: speed = 0 is equal to call stop().
   */
  void setSpeedDirection(uint8_t speed, Direction direction);

  /**
   * Stop motor, it will decrease its speed naturally.
   */
  void stop();

  /**
   * True if braked.
   */
  bool isBraked() const;
  
  /**
   * Brake the motor (that is stop and force to hold the position,
   * it consumes more power than simple stop()).
   */
  void brake();

  /**
   * Return true if contains a valid motor, false otherwise.
   * i.e. the default constructor creates a not valid motor.
   */
  explicit operator bool() const {
    return motorController != nullptr;
  }

private:
  uint8_t speed;
  Direction direction;
  bool braked;

  MotorController* motorController;

  /**
   * Constructor called by MotorController, it creates
   * the working motor.
   */
  Motor(MotorController* mc);

  /**
   * Execute command to set movement (speed and direction).
   */
  void executeMovementCommand();
  
  friend class MotorController;
};

#endif // END MOTOR_H
