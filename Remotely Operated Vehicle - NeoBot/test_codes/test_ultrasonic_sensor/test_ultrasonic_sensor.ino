/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : Ultrasonic Sensor Distance Measurement (HC-SR04)
  ------------------------------------------------------------------------------
  📄 Description:
    This code tests the HC-SR04 ultrasonic sensor with ESP32. It sends an ultrasonic
    pulse and measures the time taken for the echo to return, calculating the
    distance to an object in centimeters.

  🎯 Purpose:
    ✅ Verify ultrasonic sensor working with ESP32
    ✅ Continuously display object distance on Serial Monitor
    ✅ Base test for obstacle detection and radar-like scanning

  🔌 Wiring Connections:
    HC-SR04 Sensor       →  ESP32 Board
    -------------------------------------
    VCC                  →  5V
    GND                  →  GND
    TRIG (Trigger)       →  GPIO 5
    ECHO                 →  GPIO 18

  📚 Key Functions:
    🔹 `digitalWrite()` – Send 10µs pulse to trigger pin
    🔹 `pulseIn()`       – Measure duration of high signal on echo pin
    🔹 Distance formula: distance (cm) = (duration * 0.0343) / 2

  ⚙️ Configuration Notes:
    - Speed of sound = 343 m/s = 0.0343 cm/µs
    - Distance is divided by 2 since the signal travels to and from the object
    - Delay of 500ms between each measurement

  🧠 Code Logic Summary:
    - Trigger 10µs pulse on TRIG_PIN
    - Read echo time on ECHO_PIN
    - Calculate and print distance to Serial Monitor

  🧪 Tested On:
    - ESP32 Dev Module
    - HC-SR04 Ultrasonic Sensor
  ------------------------------------------------------------------------------
*/

#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Send pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
