#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class SensorManager {
public:
    SensorManager(int dhtPin, int mqPin, int ldrPin, int trigPin, int echoPin);

    void begin();  // Initializes all sensors

    float readTemperature();
    float readHumidity();
    int readAirQuality();
    int readLightIntensity();
    float readDistanceCM();

    void readIMU();  // Call this in loop or scheduler
    float getAccelX(), getAccelY(), getAccelZ();
    float getGyroX(), getGyroY(), getGyroZ();

private:
    int _dhtPin, _mqPin, _ldrPin, _trigPin, _echoPin;

    Adafruit_MPU6050 mpu;
    float ax, ay, az;
    float gx, gy, gz;
};

#endif
