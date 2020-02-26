# Wemos Motor Shield Remake Arduino Library
Control up to 8 DC motors through Wemos Motor Shield with Arduino.

This library is intended to replace the [original library](https://github.com/wemos/WEMOS_Motor_Shield_Arduino_Library), lacking of good design and minor facilities like getter methods.
Note that the original firmware has a major bug that blocks the entire I2C bus after few seconds of inactivity. This library mitigates such effect providing a method to force shield update, to avoid too long period of inactivity. Its up to the use to timely call this method. 
Even if this library works with original *bugged* firmware , I suggest an [alternative firmware](https://github.com/fabiuz7/wemos_motor_shield) solving definitively this bug. 

## Features
- Controls up 2 motor per shield
- Control speed
- Control direction
- Short brake
- Standby mode to save energy
- Set PWM frequency

## Usage
Instantiate the controller providing its i2c address:
    
    MotorController motorController(0x30);
    
Initialize the I2C bus and the controller:

    Wire.begin();
    motorController.begin();
    
Turn on the motor:

    Motor& motor = motorController.getFirst();
    motor.setSpeed(100);
    
Stop the motor:

    motor.setSpeed(0);
    
For a more comprehensive understanding, look at the examples or at the header files of the library. 

## Increase the maximum number of motors
The Wemos Motor Shield provides only 4 I2C selectable addresses, hence you can have only 4 Shield attached to the MCU. This leads to maximum 8 motors attached.
You may use a I2C multiplexer to support more motors, or you can design your own shield supporting more I2C solder pads, or you can design a shield support more than just 2 motors, or you can use the module to support I2C selection through I2C itself (like new [Lolin Motor Shield](https://github.com/wemos/LOLIN_I2C_MOTOR_Library)).
