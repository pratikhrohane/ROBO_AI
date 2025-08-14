#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(bool wifiConnected, bool mqttConnected, const String& command);
  void setSensorData(float temp, float hum, int gas, const String& airQuality, int light, const String& ldrDesc);

private:
  void drawHeader();
  void drawSensorPage();
  void cyclePage();

  Adafruit_SSD1306 display;

  // Icon Bitmaps (16x16)
  static const unsigned char wifiIcon[];
  static const unsigned char noWifiIcon[];
  static const unsigned char mqttIcon[];
  static const unsigned char noMqttIcon[];

  // State
  bool wifiStatus;
  bool mqttStatus;
  String lastCommand;

  float temperature;
  float humidity;
  int gasValue;
  String airQuality;
  int lightValue;
  String ldrDescription;

  unsigned long lastUpdate;
  int currentPage;
};

#endif
