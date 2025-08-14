/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : Servo Motor Sweep Test with ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test code demonstrates how to control a servo motor using the ESP32.
    The servo is rotated from 45° to 135° and then back in a smooth sweeping motion.

  🎯 Purpose:
    ✅ Test servo motor control using ESP32
    ✅ Verify PWM signal generation with Servo library
    ✅ Demonstrate sweep functionality for robotic arm or sensor positioning
    ✅ Serve as base for integrating servo-driven mechanisms into NeoBot

  🔌 Wiring Connections:
    Servo Motor          →  ESP32 Board
    -------------------------------------
    VCC (Red)            →  5V
    GND (Brown/Black)    →  GND
    Signal (Orange/Yellow) → GPIO 13

  📚 Libraries Used:
    🔹 <ESP32Servo.h>   → For generating PWM signal to control servo

  ⚙️ Configuration Notes:
    - Standard servo PWM frequency (50 Hz)
    - Min pulse width: 500 µs, Max pulse width: 2400 µs
    - Sweep range: 45° to 135° in 5° steps
    - Delay of 100 ms between each step

  🧠 Code Logic Summary:
    - Initialize servo on GPIO 13
    - Sweep forward from 45° to 135°
    - Sweep backward from 135° to 45°
    - Repeat in loop

  🧪 Tested On:
    - ESP32 Dev Module
    - SG90 Micro Servo Motor
  ------------------------------------------------------------------------------
*/

#include <ESP32Servo.h>

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);    // Standard servo frequency
  myServo.attach(13, 500, 2400); // Pin, min and max pulse width in microseconds
}

void loop() {
  // Sweep from 45° to 135°
  for (int pos = 45; pos <= 135; pos += 5) {
    myServo.write(pos);
    delay(100);
  }

  // Sweep back to 45°
  for (int pos = 135; pos >= 45; pos -= 5) {
    myServo.write(pos);
    delay(100);
  }
}
