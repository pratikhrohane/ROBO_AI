#include "WiFiManager.h"
#include "MQTTHandler.h"
#include "MotorControl.h"
#include "SensorManager.h"
#include "DisplayManager.h"

// Create global instances
WiFiManager wifiManager;

WiFiClient espClient;                // Required for MQTT
MQTTHandler mqttHandler(espClient);  // MQTT handler using WiFiClient

MotorControl motor(14, 27, 25, 33);  // Pins (IN1-IN4)

#define DHT_PIN 4    // DHT11 data pin
#define MQ_PIN 34    // MQ2 analog gas sensor pin
#define LDR_PIN 15   // LDR analog pin
#define TRIG_PIN 5   // Ultrasonic trigger pin
#define ECHO_PIN 18  // Ultrasonic echo pin

SensorManager sensors(DHT_PIN, MQ_PIN, LDR_PIN, TRIG_PIN, ECHO_PIN);

DisplayManager displayManager;

// MQTT Topics for each sensor
#define TOPIC_TEMP "roboai/neobot/sensor/dht/temperature"
#define TOPIC_HUMIDITY "roboai/neobot/sensor/dht/humidity"
#define TOPIC_GAS_AIR "roboai/neobot/sensor/mq2"
#define TOPIC_LDR "roboai/neobot/sensor/ldr"
#define TOPIC_IMU_ACCEL "roboai/neobot/sensor/imu/accel"
#define TOPIC_IMU_GYRO "roboai/neobot/sensor/imu/gyro"
#define TOPIC_DISTANCE "roboai/neobot/sensor/distance"

unsigned long lastSensorPublishTime = 0;
const unsigned long SENSOR_PUBLISH_INTERVAL = 2000;  // 2 seconds

String cmd = "None";

// Callback function to handle incoming MQTT messages
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT Message received on topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  if (String(topic) == "roboai/neobot/command") {
    Serial.print("Command received: ");
    Serial.println(msg);
    // Handle command
    if (msg == "FWD") motor.moveForward();
    else if (msg == "BWD") motor.moveBackward();
    else if (msg == "LFT") motor.turnLeft();
    else if (msg == "RHT") motor.turnRight();
    else if (msg == "STP") motor.stop();

    cmd = msg;
  }
  Serial.println();
}

void publishSensorData() {
  float temperature = sensors.readTemperature();
  float humidity = sensors.readHumidity();
  int ldrValue = sensors.readLightIntensity();
  int gasValue = sensors.readAirQuality();
  float distanceCM = sensors.readDistanceCM();

  mqttHandler.publish(TOPIC_TEMP, String(temperature, 2).c_str());
  mqttHandler.publish(TOPIC_HUMIDITY, String(humidity, 2).c_str());
  mqttHandler.publish(TOPIC_LDR, String(ldrValue).c_str());
  mqttHandler.publish(TOPIC_GAS_AIR, String(gasValue).c_str());
  mqttHandler.publish(TOPIC_DISTANCE, String(distanceCM, 2).c_str());


  // IMU Data
  sensors.readIMU();  // Always update latest values

  // Format accel: "x,y,z"
  String accelData = String(sensors.getAccelX(), 2) + "," + String(sensors.getAccelY(), 2) + "," + String(sensors.getAccelZ(), 2);
  // Format gyro: "x,y,z"
  String gyroData = String(sensors.getGyroX(), 2) + "," + String(sensors.getGyroY(), 2) + "," + String(sensors.getGyroZ(), 2);

  mqttHandler.publish(TOPIC_IMU_ACCEL, accelData.c_str());
  mqttHandler.publish(TOPIC_IMU_GYRO, gyroData.c_str());
}

void displaySensorData() {
  float temperature = sensors.readTemperature();
  float humidity = sensors.readHumidity();
  int ldrValue = sensors.readLightIntensity();  // 0-1023
  int gasValue = sensors.readAirQuality();      // 0-1023

  // Air Quality Interpretation
  String airStatus;
  if (gasValue < 200) {
    airStatus = "Good";
  } else if (gasValue < 400) {
    airStatus = "Moderate";
  } else {
    airStatus = "Poor";
  }

  // Light Condition Interpretation
  String lightStatus = (ldrValue > 600) ? "Day" : "Night";

  // Pass to DisplayManager
  displayManager.setSensorData(
    temperature,
    humidity,
    gasValue,
    airStatus,
    ldrValue,
    lightStatus
  );
}


void setup() {
  Serial.begin(115200);

  displayManager.begin();
  displayManager.update(false, false, cmd);

  // Connect to Wi-Fi
  wifiManager.begin("Openavia", "Abcdefgh.3220");

  // Configure MQTT with broker address and client ID
  mqttHandler.begin("broker.hivemq.com", 1883, "esp32_robot_01");

  // Register callback for incoming messages
  mqttHandler.setCallback(onMqttMessage);

  // Connect to MQTT broker
  if (mqttHandler.connect()) {
    Serial.println("MQTT connected successfully.");

    // Subscribe to control topic
    mqttHandler.subscribe("roboai/neobot/command");

    // Publish startup message
    mqttHandler.publish("roboai/neobot/log", "System started.");
  } else {
    Serial.println("MQTT connection failed.");
  }

  motor.begin();

  sensors.begin();

  displayManager.begin();
  displayManager.update(false, false, cmd);
}

void loop() {
  // Ensure Wi-Fi stays connected
  wifiManager.reconnectIfNeeded();

  // Reconnect to MQTT if needed
  if (!mqttHandler.isConnected()) {
    mqttHandler.connect();
  }

  // Handle periodic sensor publishing
  unsigned long currentMillis = millis();
  if (currentMillis - lastSensorPublishTime >= SENSOR_PUBLISH_INTERVAL) {
    lastSensorPublishTime = currentMillis;
    publishSensorData();          // Publish to MQTT or OLED
    displaySensorData();
  }

  displayManager.update(wifiManager.isConnected(), mqttHandler.isConnected(), cmd);

  // Handle incoming MQTT messages
  mqttHandler.loop();
}
