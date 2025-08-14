/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : ESP32 MQTT JSON Publisher - Sensor Test
  ------------------------------------------------------------------------------
  📄 Description:
    This sketch simulates sensor data and publishes it in JSON format to an MQTT
    broker using the ESP32. It includes mock values for temperature, humidity,
    gas, LDR, and IMU (accelerometer + gyroscope), and demonstrates JSON encoding.

  🎯 Purpose:
    ✅ Simulate sensor telemetry for remote monitoring via MQTT
    ✅ Practice creating structured JSON payloads with nested data
    ✅ Test MQTT connectivity, reconnection, and publishing
    ✅ Validate MQTT broker communication (HiveMQ public broker)

  🔌 Wiring Connections:
    No external sensors required. All data is generated programmatically.

  📚 Libraries Used:
    🔹 <WiFi.h>              → Connect ESP32 to local Wi-Fi network
    🔹 <PubSubClient.h>      → MQTT communication (publish/subscribe)
    🔹 <ArduinoJson.h>       → JSON serialization of mock sensor data

  ⚙️ Configuration Notes:
    - Wi-Fi credentials must be correct to establish connection
    - Uses broker.hivemq.com as the MQTT broker (port 1883, no auth)
    - JSON payload includes simulated sensor values and command info
    - Data is sent every 5 seconds (adjustable via `interval`)

  🧠 Code Logic Summary:
    - Connect to Wi-Fi
    - Connect to MQTT broker
    - Every 5 seconds:
        ⮞ Simulate sensor readings
        ⮞ Package them into a nested JSON object
        ⮞ Publish to "robot/sensors/data" topic
        ⮞ Print JSON to Serial for debugging

  🧪 Tested On:
    - ESP32 DevKit v1
    - HiveMQ MQTT Broker (public)
  ------------------------------------------------------------------------------
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Wi-Fi Credentials
const char* ssid = "Openavia";
const char* password = "Abcdefgh.3220";

// MQTT Broker Configuration
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "robot/sensors/data";

// MQTT and Wi-Fi Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Timing Variables
unsigned long lastMsg = 0;
const long interval = 5000;  // Interval between publishes (ms)

// Mock command value (could be updated externally)
String last_command = "forward";

// Connect to Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Reconnect to MQTT broker if disconnected
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds...");
      delay(5000);
    }
  }
}

// Setup runs once on boot
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

// Main loop: publish data periodically
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    // Simulate sensor data
    float temperature = random(250, 350) / 10.0;   // 25.0 to 35.0 °C
    float humidity = random(400, 700) / 10.0;      // 40% to 70%
    int gas_value = random(1800, 2200);            // Gas sensor mock
    int ldr_value = random(300, 900);              // Light sensor mock

    // IMU - Accelerometer values (x, y, z)
    float accel_x = random(-100, 100) / 100.0;
    float accel_y = random(-100, 100) / 100.0;
    float accel_z = 9.8;  // Static Z value

    // IMU - Gyroscope values (x, y, z)
    float gyro_x = random(-50, 50) / 100.0;
    float gyro_y = random(-50, 50) / 100.0;
    float gyro_z = random(-50, 50) / 100.0;

    // Create and structure JSON object
    StaticJsonDocument<512> doc;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["gas_value"] = gas_value;
    doc["ldr_value"] = ldr_value;

    JsonObject imu = doc.createNestedObject("imu");

    JsonObject accel = imu.createNestedObject("accel");
    accel["x"] = accel_x;
    accel["y"] = accel_y;
    accel["z"] = accel_z;

    JsonObject gyro = imu.createNestedObject("gyro");
    gyro["x"] = gyro_x;
    gyro["y"] = gyro_y;
    gyro["z"] = gyro_z;

    doc["last_command"] = last_command;

    // Serialize and publish JSON
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    Serial.println("Publishing JSON to MQTT:");
    Serial.println(jsonBuffer);

    client.publish(mqtt_topic, jsonBuffer);
  }
}
