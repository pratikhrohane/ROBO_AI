/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : DHT Sensor - Temperature and Humidity Test with ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test sketch reads temperature and humidity values from a DHT sensor
    (DHT11 or DHT22) and prints the readings to the Serial Monitor every 2 seconds.

  🎯 Purpose:
    ✅ Test sensor wiring and communication with ESP32
    ✅ Verify accurate temperature and humidity readings
    ✅ Use this as a reference for environmental monitoring integration in NeoBot

  🔌 Wiring Connections:
    DHT Sensor         →  ESP32 Board
    -------------------------------------
    VCC                →  3.3V or 5V
    GND                →  GND
    DATA               →  GPIO 4 (modifiable)
    Optional           →  10kΩ pull-up resistor between DATA and VCC

  📚 Libraries Used:
    🔹 <DHT.h> → For reading data from DHT11/DHT22 sensors

  ⚙️ Configuration Notes:
    - GPIO pin is defined using `#define DHTPIN`
    - Sensor type selected using `#define DHTTYPE`
    - 2-second delay between readings (required for sensor stability)

  🧠 Code Logic Summary:
    - Initialize DHT sensor and serial monitor
    - Read temperature and humidity values
    - Print results to serial output
    - Retry reading if sensor returns invalid data

  🧪 Tested On:
    - ESP32 Dev Module
    - DHT11 and DHT22 (both tested and compatible)
  ------------------------------------------------------------------------------
*/

#include <DHT.h>

// Define the GPIO pin and sensor type
#define DHTPIN 4           // GPIO 4 connected to DHT DATA pin
#define DHTTYPE DHT11      // DHT11 or DHT22 (change if needed)

// Create a DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);         // Initialize Serial communication
  delay(1000);                  // Optional startup delay
  Serial.println("Initializing DHT Sensor...");
  dht.begin();                  // Start the DHT sensor
}

void loop() {
  delay(2000);  // Minimum delay required between reads

  // Read humidity and temperature (Celsius)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check for read errors
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    return;
  }

  // Print the sensor values
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
