/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : LDR Digital Light Sensor Test with ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test reads the digital output from an LDR (Light Dependent Resistor)
    module and prints whether light or darkness is detected via Serial Monitor.

  🎯 Purpose:
    ✅ Verify digital signal from LDR module to ESP32
    ✅ Confirm light/darkness detection logic
    ✅ Serve as reference for ambient light–based automation in NeoBot

  🔌 Wiring Connections:
    LDR Module           →  ESP32 Board
    -------------------------------------
    VCC                  →  3.3V
    GND                  →  GND
    OUT (Digital)        →  GPIO 15

  📚 Libraries Used:
    ❌ None (uses built-in Arduino functions)

  ⚙️ Configuration Notes:
    - LDR module has onboard comparator with adjustable sensitivity (potentiometer)
    - Outputs LOW when light is detected, HIGH in darkness
    - Detection status printed every 500ms

  🧠 Code Logic Summary:
    - Set LDR digital pin as input
    - Read pin state using digitalRead()
    - Print light or darkness status accordingly

  🧪 Tested On:
    - ESP32 Dev Module
    - Generic LDR Digital Sensor Module with comparator
  ------------------------------------------------------------------------------
*/

#define LDR_DIGITAL_PIN  15  // Change to your connected digital pin

void setup() {
  Serial.begin(115200);
  pinMode(LDR_DIGITAL_PIN, INPUT);
}

void loop() {
  int lightState = digitalRead(LDR_DIGITAL_PIN);

  if (lightState == LOW) {
    Serial.println("💡 Light Detected");
  } else {
    Serial.println("🌑 Darkness Detected");
  }

  delay(500);
}
