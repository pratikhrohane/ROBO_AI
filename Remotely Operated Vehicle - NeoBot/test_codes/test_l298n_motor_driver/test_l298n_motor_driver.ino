/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : BO Motor Test using L298N Motor Driver and ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test code controls a two-motor differential drive robot using L298N and ESP32.
    It sequentially tests: Forward → Backward → Left → Right → Stop → Loop

  🎯 Purpose:
    - Verify direction control of both motors
    - Validate wiring and GPIO pin configuration
    - Use as a basic diagnostic for movement testing

  🔌 Wiring Connections:
    L298N Motor Driver  →  ESP32 Board
    -------------------------------------
    IN1 (Left FWD)      →  GPIO 14
    IN2 (Left BWD)      →  GPIO 27
    IN3 (Right FWD)     →  GPIO 25
    IN4 (Right BWD)     →  GPIO 33
    ENA/ENB             →  Jumpered (motors always enabled)
    GND (L298N)         →  GND (ESP32)
    VCC (L298N)         →  External Motor Supply (6V–12V)

  📚 Libraries Used:
    - No external libraries required (pure Arduino functions)

  ⚙️ Configuration Notes:
    - Speed control is not implemented in this test (No PWM)
    - Uses blocking delay() functions for simple timed actions

  🧠 Code Logic Summary:
    - Set motor pins as OUTPUT
    - Perform the following motion tests in sequence:
      → Forward → Stop → Backward → Stop → Left → Stop → Right → Stop
    
  🧪 Tested On:
    - ESP32 Dev Module
    - L298N Dual H-Bridge Motor Driver
    - 4x BO Motors (DC)
  ------------------------------------------------------------------------------
*/

// Define GPIO pins connected to L298N motor driver
#define IN1 14  // Left motor forward
#define IN2 27  // Left motor backward
#define IN3 25  // Right motor forward
#define IN4 33  // Right motor backward

void setup() {
  // Set motor control pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // ---- Move Forward ----
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);

  // ---- Stop Motors ----
  stopMotors();
  delay(1000);

  // ---- Move Backward ----
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  // ---- Stop Motors ----
  stopMotors();
  delay(1000);

  // ---- Turn Left (Right motor forward only) ----
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1500);

  // ---- Stop Motors ----
  stopMotors();
  delay(1000);

  // ---- Turn Right (Left motor forward only) ----
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1500);

  // ---- Stop Motors ----
  stopMotors();
  delay(2000);  // Pause before next loop
}

// 🛑 Stop both motors (Helper Function)
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
