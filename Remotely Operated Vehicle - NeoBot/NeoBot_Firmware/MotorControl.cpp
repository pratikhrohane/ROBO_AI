#include "MotorControl.h"

// Constructor: Save motor pin numbers
MotorControl::MotorControl(int in1, int in2, int in3, int in4) {
    _in1 = in1;
    _in2 = in2;
    _in3 = in3;
    _in4 = in4;
}

// Setup motor pins
void MotorControl::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);
    stop(); // Start with all motors off
}

// Move forward
void MotorControl::moveForward() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, HIGH);
}

// Move backward
void MotorControl::moveBackward() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
}

// Turn left
void MotorControl::turnLeft() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
}

// Turn right
void MotorControl::turnRight() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, HIGH);
}

// Stop motors
void MotorControl::stop() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
}
