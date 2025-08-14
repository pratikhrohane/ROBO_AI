#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <WiFi.h>
#include <PubSubClient.h>

// MQTTHandler class: manages MQTT client setup, connection, publish, and subscribe
class MQTTHandler {
public:
  MQTTHandler(WiFiClient& wifiClient);  // Constructor

  void begin(const char* broker, uint16_t port, const char* clientId);  // Set broker details
  bool connect();                                                       // Attempt MQTT connection
  void loop();                                                          // Handle incoming/outgoing MQTT traffic
  bool isConnected();                                                   // Check if MQTT is connected
  void publish(const char* topic, const char* message);                 // Publish to topic
  void subscribe(const char* topic);                                    // Subscribe to topic
  void setCallback(MQTT_CALLBACK_SIGNATURE);                            // Set callback for incoming messages

private:
  WiFiClient& _wifiClient;
  PubSubClient _mqttClient;
  const char* _broker;
  uint16_t _port;
  const char* _clientId;
};

#endif
