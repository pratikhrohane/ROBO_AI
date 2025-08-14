#include "SensorManager.h"
#include <DHT.h>

#define DHTTYPE DHT11         // Or DHT22
DHT dhtInstance(0, DHTTYPE);  // Dummy, will set pin in constructor

SensorManager::SensorManager(int dhtPin, int mqPin, int ldrPin, int trigPin, int echoPin)
  : _dhtPin(dhtPin), _mqPin(mqPin), _ldrPin(ldrPin), _trigPin(trigPin), _echoPin(echoPin),
    ax(0), ay(0), az(0), gx(0), gy(0), gz(0) {
  dhtInstance = DHT(_dhtPin, DHTTYPE);
}


void SensorManager::begin() {
  dhtInstance.begin();
  pinMode(_mqPin, INPUT);
  pinMode(_ldrPin, INPUT);
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("❌ MPU6050 not found!");
  } else {
    Serial.println("✅ MPU6050 ready!");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }
}

float SensorManager::readTemperature() {
  return dhtInstance.readTemperature();
}

float SensorManager::readHumidity() {
  return dhtInstance.readHumidity();
}

int SensorManager::readAirQuality() {
  return analogRead(_mqPin);
}

int SensorManager::readLightIntensity() {
  return analogRead(_ldrPin);
}

float SensorManager::readDistanceCM() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  long duration = pulseIn(_echoPin, HIGH);
  return duration * 0.0343 / 2;
}

// ---------------- IMU -----------------

void SensorManager::readIMU() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;

  gx = g.gyro.x;
  gy = g.gyro.y;
  gz = g.gyro.z;
}

// IMU getters
float SensorManager::getAccelX() {
  return ax;
}
float SensorManager::getAccelY() {
  return ay;
}
float SensorManager::getAccelZ() {
  return az;
}
float SensorManager::getGyroX() {
  return gx;
}
float SensorManager::getGyroY() {
  return gy;
}
float SensorManager::getGyroZ() {
  return gz;
}
