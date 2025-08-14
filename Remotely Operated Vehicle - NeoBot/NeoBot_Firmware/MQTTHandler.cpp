#include "MQTTHandler.h"

// Constructor: initializes internal MQTT client
MQTTHandler::MQTTHandler(WiFiClient& wifiClient) 
    : _wifiClient(wifiClient), _mqttClient(wifiClient),
      _broker(nullptr), _port(0), _clientId(nullptr) {}

// Configure MQTT broker and client ID
void MQTTHandler::begin(const char* broker, uint16_t port, const char* clientId) {
    _broker = broker;
    _port = port;
    _clientId = clientId;
    _mqttClient.setServer(_broker, _port);
}

// Attempt to connect to MQTT broker
bool MQTTHandler::connect() {
    if (!_mqttClient.connected()) {
        return _mqttClient.connect(_clientId);
    }
    return true;
}

// Process MQTT messages and maintain connection
void MQTTHandler::loop() {
    _mqttClient.loop();
}

// Check MQTT connection status
bool MQTTHandler::isConnected() {
    return _mqttClient.connected();
}

// Publish message to topic
void MQTTHandler::publish(const char* topic, const char* message) {
    _mqttClient.publish(topic, message);
}

// Subscribe to topic
void MQTTHandler::subscribe(const char* topic) {
    _mqttClient.subscribe(topic);
}

// Set callback function for incoming messages
void MQTTHandler::setCallback(MQTT_CALLBACK_SIGNATURE) {
    _mqttClient.setCallback(callback);
}
