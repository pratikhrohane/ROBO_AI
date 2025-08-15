# 🤖 NeoBot – Remotely Operated Vehicle (ROV)

## 📌 Overview
**NeoBot** is a remotely operated robotic vehicle that integrates multiple environmental sensors, an OLED display for live data, and MQTT over Wi-Fi for real-time remote monitoring.  
It is designed to enter environments that are **unsafe or inaccessible** to humans and provide detailed environmental data.

---

## 🛑 Problem
Human access to certain environments is unsafe - examples include:
- Polluted areas
- Confined spaces
- Chemical spill zones
- Hazardous industrial areas

---

## 💡 Solution
NeoBot can:
- Move into dangerous or restricted spaces
- Measure **temperature**, **humidity**, **air quality**, **gas concentration**, and **light intensity**
- Send data remotely via **MQTT over Wi-Fi**
- Provide **live camera feed** for remote navigation

---

## 🌍 Applications
- 🏭 **Factory floor air quality checks**
- 🌱 **Indoor farming climate monitoring**
- ⛏ **Mining tunnel environmental surveys**
- 🧪 **Chemical plant safety inspections**
- 🚨 **Disaster response in hazardous zones**

---

## 🛠 Tech Stack

### **Hardware**
- **4WD Double Layer Smart Car Chassis Kit**
- **ESP32 Dev Board** (Main controller)
- **OLED Display** (SSD1306, 128x64, I2C)
- **DHT11** (Temperature & humidity)
- **MQ2 Gas Sensor** (Gas concentration & air quality)
- **LDR** (Light detection – day/night)
- **HC-SR04 Ultrasonic Sensor** (Distance measurement)
- **MPU6050** (Accelerometer & gyroscope)
- **Smartphone** (Camera feed – via IV Cam or Python WebRTC)
- **7V Power Supply**
- **L298N Motor Driver**
- **SG90 Servo Motor**

### **Software**
- Arduino IDE / VS Code 
- Python (PyQt5)
- C++ (Arduino programming)
- MQTT (PubSubClient, Mosquitto broker)
- IV Cam (For camera streaming)

---

## 📡 Communication & MQTT Topics

```cpp
#define TOPIC_TEMP        "roboai/neobot/sensor/dht/temperature"
#define TOPIC_HUMIDITY    "roboai/neobot/sensor/dht/humidity"
#define TOPIC_GAS_AIR     "roboai/neobot/sensor/mq2"
#define TOPIC_LDR         "roboai/neobot/sensor/ldr"
#define TOPIC_IMU_ACCEL   "roboai/neobot/sensor/imu/accel"
#define TOPIC_IMU_GYRO    "roboai/neobot/sensor/imu/gyro"
#define TOPIC_DISTANCE    "roboai/neobot/sensor/distance"
````

---

## 📚 Libraries Used

* [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit MPU6050](https://github.com/adafruit/Adafruit_MPU6050)
* [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
* [PubSubClient](https://github.com/knolleary/pubsubclient)
* **WiFi** (built-in ESP32)
* **Wire** (built-in for I2C)

---

## 🖥 PyQt5 Control UI Panels

* **Sensor Panel** → Displays Temperature, Humidity, Gas Quality, Day/Night status
* **IMU Panel** → Shows accelerometer & gyroscope values with 3D orientation
* **Camera Panel** → Live video stream
* **Radar Panel** → Visual radar with obstacle detection
* **Control Panel** → Remote movement control for the robot
* **Log Panel** → Logs warnings, errors, and transmission states

---

## 🛠 Robot Development

📸 **Hardware Build**

```
[Images of robot in 2-row × 3-column layout]
```

---
## 🌐 MQTT WebSocket & HiveMQ 
During development, **HiveMQ** was used as a public MQTT broker to quickly test and verify sensor data transmission over **WebSockets**.  
This allowed rapid debugging without setting up a local broker.

**Steps:**
1. Connect ESP32 to HiveMQ public broker.
2. Subscribe to topics in HiveMQ WebSocket dashboard.
3. Verify incoming sensor data in real-time.

📸 **HiveMQ Dashboard**
![HiveMQ Dashboard](images/hivemq_dashboard.png)
---

## 🎥 Demo Video

📹 **Watch Here:** [Demo Link](https://example.com)

---



## 🧠 Future Improvements

* WebRTC-based live camera streaming without third-party apps
* Autonomous navigation using AI
* Mobile app for remote control

---


