/*
  ------------------------------------------------------------------------------
  Project     : RoboAi - NeoBot: Remotely Operated Vehicle
  Test Code   : OLED UI Display Test with Icons and Rotating Sensor Data
  ------------------------------------------------------------------------------
  📄 Description:
    This sketch demonstrates how to sensor data, status icons, and commands
    on a 128x64 OLED display using the Adafruit SSD1306 library. It simulates
    data display pages and toggles MQTT/Wi-Fi status icons.

  🎯 Purpose:
    ✅ Test OLED screen rendering with Adafruit SSD1306 library
    ✅ Display rotating pages for different sensor values
    ✅ Embed 16x16 bitmap icons for Wi-Fi and MQTT statuses
    ✅ Preview UI/UX layout before adding real sensor data

  🔌 Wiring Connections:
    OLED Display (SSD1306) → ESP32 Board (I2C)
    ------------------------------------------
    VCC                    → 3.3V
    GND                    → GND
    SDA                    → GPIO 21 (default I2C)
    SCL                    → GPIO 22 (default I2C)

  📚 Libraries Used:
    🔹 <Wire.h>               → I2C communication
    🔹 <Adafruit_GFX.h>       → Core graphics functions
    🔹 <Adafruit_SSD1306.h>   → OLED driver for SSD1306

  ⚙️ Configuration Notes:
    - Screen resolution: 128x64 pixels
    - I2C Address: 0x3C (common for SSD1306)
    - Icons: 16x16 pixel bitmaps (MQTT & Wi-Fi)
    - Page auto-rotation: Every 3 seconds

  🧠 Code Logic Summary:
    - Initialize display and show mock sensor pages
    - Draw status icons in the header
    - Switch between 3 pages: Temp & Humidity, Gas & Air Quality, Light & LDR
    - Show last received command at the bottom

  🧪 Tested On:
    - ESP32 Dev Module
    - 0.96" I2C OLED Display (SSD1306 128x64)
  ------------------------------------------------------------------------------
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 16x16 Icons for MQTT and Wi-Fi
const unsigned char epd_bitmap_icons8_wifi_16 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x1f, 0xf8, 0x3c, 0x3c, 0x70, 0x0e, 0x07, 0xe0, 
  0x0f, 0xf0, 0x08, 0x10, 0x03, 0xc0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char epd_bitmap_icons8_no_wifi_16 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x19, 0x98, 0x21, 0x84, 0x47, 0xe2, 0x09, 0x90, 
  0x11, 0x88, 0x02, 0x40, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char epd_bitmap_icons8_mqtt_16 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x06, 0x60, 0x0c, 0x20, 0x08, 0x10, 0x38, 0x1c, 
  0x60, 0x46, 0x42, 0xe2, 0x42, 0xe2, 0x22, 0x44, 0x1a, 0x58, 0x02, 0x40, 0x07, 0x40, 0x02, 0x00
};
const unsigned char epd_bitmap_icons8_no_mqtt_16 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x06, 0x60, 0x0c, 0x20, 0x08, 0x10, 0x38, 0x1c, 
  0x60, 0x04, 0x40, 0x00, 0x40, 0x26, 0x20, 0x1c, 0x1f, 0xd8, 0x00, 0x34, 0x00, 0x22, 0x00, 0x00
};

// State variables
int sensor_page = 0;
unsigned long last_update = 0;
const unsigned long interval = 3000; // 3 seconds
String last_command = "Forward";

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ OLED initialization failed!");
    while (true); // Halt
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();
}

void drawHeader() {
  display.fillRect(0, 0, 128, 16, BLACK); // Clear header

  // Icons: Left = MQTT inactive, Right = Wi-Fi active (mocked)
  display.drawBitmap(0, 0, epd_bitmap_icons8_no_mqtt_16, 16, 16, WHITE);
  display.drawBitmap(112, 0, epd_bitmap_icons8_wifi_16, 16, 16, WHITE);
}

void drawSensorPage(int page) {
  display.fillRect(0, 16, 128, 48, BLACK); // Clear main display area

  display.setCursor(5, 20);
  switch (page) {
    case 0:
      display.println("Temp: 28.5 C");
      display.setCursor(5, 35);
      display.println("Humidity: 58%");
      break;
    case 1:
      display.println("Gas MQ2: 2050");
      display.setCursor(5, 35);
      display.println("Air Quality: OK");
      break;
    case 2:
      display.println("Light: 356");
      display.setCursor(5, 35);
      display.println("LDR: Dim");
      break;
  }

  display.setCursor(5, 50);
  display.print("Last Cmd: ");
  display.println(last_command);
}

void loop() {
  if (millis() - last_update > interval) {
    sensor_page = (sensor_page + 1) % 3;
    last_update = millis();
  }

  drawHeader();
  drawSensorPage(sensor_page);

  display.display();
}
