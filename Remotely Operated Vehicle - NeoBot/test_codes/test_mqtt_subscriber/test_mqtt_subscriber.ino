/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : MQTT Command Receiver
  ------------------------------------------------------------------------------
  📄 Description:
    This sketch connects the ESP32 to a Wi-Fi network and subscribes to a public
    MQTT broker. It listens for movement commands (forward, backward, left, right,
    stop) on a specified topic and displays the received command on the Serial Monitor.

  🎯 Purpose:
    ✅ Connect to Wi-Fi and MQTT broker
    ✅ Subscribe to movement command topic
    ✅ Receive and print robot control commands
    ✅ Base code for integrating with motor driver logic

  📡 MQTT Communication:
    Broker         → broker.hivemq.com
    Port           → 1883 (non-TLS)
    Subscribe To   → robot/command
    Expected Msgs  → "forward", "backward", "left", "right", "stop"

  🔌 Wiring Connections:
    None required (MQTT-only test)

  📚 Libraries Used:
    🔹 <WiFi.h>            → Wi-Fi connectivity
    🔹 <PubSubClient.h>    → MQTT client library

  ⚙️ Configuration Notes:
    - Wi-Fi SSID: Openavia
    - MQTT Broker: HiveMQ public broker (no credentials)
    - Commands are case-sensitive
    - Extend logic to control motors using L298N driver

  🧠 Code Logic Summary:
    - Connect to Wi-Fi and broker
    - Subscribe to a command topic
    - Print any received message via Serial
    - Handle reconnect if connection drops

  🧪 Tested On:
    - ESP32 Dev Module
    - HiveMQ Public Broker
  ------------------------------------------------------------------------------
*/

#include <WiFi.h>            // For Wi-Fi connectivity
#include <PubSubClient.h>    // For MQTT communication

// Replace with your Wi-Fi credentials
const char* ssid = "Openavia";
const char* password = "";

// MQTT broker details
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "robot/command";

// Wi-Fi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Function to connect to Wi-Fi
void setup_wifi() {
  delay(100);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);  // Start connecting to Wi-Fi

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Wi-Fi connected
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback function for received MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("]: ");

  String message = "";

  // Convert byte array to string
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Print received message
  Serial.println(message);

  // Optional: You can handle motor logic based on command here
  // Example:
  // if (message == "forward") { moveForward(); }
}

// Function to connect/reconnect to MQTT broker
void reconnect() {
  // Loop until connected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect with client ID
    if (client.connect("ESP32Client")) {
      Serial.println("connected!");
      // Subscribe to the command topic
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000); // Wait before retrying
    }
  }
}

void setup() {
  Serial.begin(115200);       // Start serial communication
  setup_wifi();               // Connect to Wi-Fi
  client.setServer(mqtt_server, 1883);    // Set broker address and port
  client.setCallback(callback);           // Set callback for received messages
}

void loop() {
  // Reconnect if MQTT disconnected
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Process incoming messages and keep alive
}
