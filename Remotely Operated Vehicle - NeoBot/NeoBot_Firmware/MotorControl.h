#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class MotorControl {
public:
    MotorControl(int in1, int in2, int in3, int in4);

    void begin();                // Setup pin modes
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stop();

private:
    int _in1, _in2, _in3, _in4;
};

#endif
