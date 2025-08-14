/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : MPU6050 - Accelerometer, Gyroscope & Temperature Test with ESP32
  ------------------------------------------------------------------------------
  📄 Description:
    This test reads real-time raw accelerometer, gyroscope, and temperature data
    from the MPU6050 sensor and prints values to the Serial Monitor via I2C.

  🎯 Purpose:
    ✅ Verify I2C communication between ESP32 and MPU6050
    ✅ Test basic accelerometer and gyroscope functionality
    ✅ Check onboard temperature reading
    ✅ Serve as reference for integrating motion sensing into NeoBot

  🔌 Wiring Connections:
    MPU6050 Module       →  ESP32 Board
    -------------------------------------
    VCC                  →  3.3V
    GND                  →  GND
    SDA                  →  GPIO 21
    SCL                  →  GPIO 22

  📚 Libraries Used:
    🔹 <Wire.h>              → For I2C communication
    🔹 <Adafruit_MPU6050.h>  → Interface for MPU6050
    🔹 <Adafruit_Sensor.h>   → Common sensor wrapper used by Adafruit

  ⚙️ Configuration Notes:
    - Accelerometer range set to ±8G
    - Gyroscope range set to ±500°/s
    - Filter bandwidth set to 21 Hz
    - Sensor values printed every 500ms

  🧠 Code Logic Summary:
    - Initialize Serial and I2C
    - Begin MPU6050 sensor and configure ranges
    - Read values using getEvent()
    - Print: Accel (m/s²), Gyro (rad/s), Temp (°C)

  🧪 Tested On:
    - ESP32 Dev Module
    - GY-521 MPU6050 IMU Module
  ------------------------------------------------------------------------------
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Create MPU6050 object
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);              // Start Serial Monitor
  while (!Serial) delay(10);         // Wait for Serial to connect (USB only)

  Serial.println("Initializing MPU6050...");

  // Start I2C and initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("❌ Failed to find MPU6050 chip. Check wiring!");
    while (1) delay(10);  // Halt if not found
  }

  Serial.println("✅ MPU6050 Found!");

  // Configure sensor ranges (optional)
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);  // Let sensor settle
}

void loop() {
  // Create sensor event containers
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);  // Read all sensor values

  // ---- Print Accelerometer ----
  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);

  // ---- Print Gyroscope ----
  Serial.print("\nGyro  X: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s, Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);

  // ---- Print Temperature ----
  Serial.print("\nTemp     : ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.println("-----------------------------------------------------");
  delay(500);  // Wait before next reading
}
