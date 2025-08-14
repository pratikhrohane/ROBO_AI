/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : MQ2 Gas Sensor Test with ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test reads analog data from the MQ2 gas sensor and prints raw gas
    concentration values to the Serial Monitor. Useful for checking the sensor's
    basic functionality and responsiveness to smoke, LPG, or other gases.

  🎯 Purpose:
    - Verify MQ2 sensor connection and analog reading on ESP32
    - Monitor gas concentration (in raw analog form)
    - Help calibrate threshold for gas alert conditions later

  🔌 Wiring Connections:
    MQ2 Gas Sensor      →  ESP32 Board
    -------------------------------------
    AO (Analog Out)     →  GPIO 34 (Analog Input)
    VCC                 →  3.3V or 5V (based on module)
    GND                 →  GND

  📚 Libraries Used:
    - No external libraries required

  ⚙️ Configuration Notes:
    - Uses analogRead() on GPIO 34 (ESP32 supports ADC on this pin)
    - Raw value range: ~0 to 4095 (depending on gas concentration)
    - No digital threshold or buzzer used in this test

  🧠 Code Logic Summary:
    - Initialize Serial Monitor
    - Read analog value from MQ2 sensor
    - Print reading every 1 second

  🧪 Tested On:
    - ESP32 Dev Module
    - MQ2 Gas Sensor Module (analog output)
  ------------------------------------------------------------------------------
*/

// GPIO pin connected to MQ2 analog output
const int mq2Pin = 34;  // Analog input pin (ADC1 channel 6 on ESP32)

void setup() {
  Serial.begin(115200);     // Start serial communication at 115200 baud
  pinMode(mq2Pin, INPUT);   // Set MQ2 pin as input
}

void loop() {
  // Read analog signal from MQ2 sensor
  int gasValue = analogRead(mq2Pin);

  // Print gas concentration level (raw value)
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  delay(1000);  // Wait for 1 second before next read
}
