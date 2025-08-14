#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET),
    wifiStatus(false), mqttStatus(false),
    temperature(0), humidity(0), gasValue(0),
    airQuality(""), lightValue(0), ldrDescription(""),
    lastCommand(""), lastUpdate(0), currentPage(0) {}

void DisplayManager::begin() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("❌ OLED initialization failed"));
    while (true); // Halt
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();
}

void DisplayManager::setSensorData(float temp, float hum, int gas, const String& air, int light, const String& ldrDesc) {
  temperature = temp;
  humidity = hum;
  gasValue = gas;
  airQuality = air;
  lightValue = light;
  ldrDescription = ldrDesc;
}

void DisplayManager::update(bool wifiConnected, bool mqttConnected, const String& command) {
  if (millis() - lastUpdate > 3000) {
    cyclePage();
    lastUpdate = millis();
  }

  wifiStatus = wifiConnected;
  mqttStatus = mqttConnected;
  lastCommand = command;

  drawHeader();
  drawSensorPage();
  display.display();
}

void DisplayManager::cyclePage() {
  currentPage = (currentPage + 1) % 3;
}

void DisplayManager::drawHeader() {
  display.fillRect(0, 0, SCREEN_WIDTH, 16, BLACK);
  display.drawBitmap(0, 0, mqttStatus ? mqttIcon : noMqttIcon, 16, 16, WHITE);
  display.drawBitmap(SCREEN_WIDTH - 16, 0, wifiStatus ? wifiIcon : noWifiIcon, 16, 16, WHITE);
}

void DisplayManager::drawSensorPage() {
  display.fillRect(0, 16, SCREEN_WIDTH, 48, BLACK);
  display.setCursor(5, 20);

  switch (currentPage) {
    case 0:
      display.printf("Temp: %.1f C\n", temperature);
      display.setCursor(5, 35);
      display.printf("Humidity: %.1f %%\n", humidity);
      break;
    case 1:
      display.printf("Gas MQ2: %d\n", gasValue);
      display.setCursor(5, 35);
      display.printf("Air Quality: %s\n", airQuality.c_str());
      break;
    case 2:
      display.printf("Light: %d\n", lightValue);
      display.setCursor(5, 35);
      display.printf("LDR: %s\n", ldrDescription.c_str());
      break;
  }

  display.setCursor(5, 50);
  display.print("Last Cmd: ");
  display.println(lastCommand);
}

// Icon bitmaps
const unsigned char DisplayManager::wifiIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x1F, 0xF8, 0x3C, 0x3C, 0x70, 0x0E, 0x07, 0xE0,
  0x0F, 0xF0, 0x08, 0x10, 0x03, 0xC0, 0x03, 0xC0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char DisplayManager::noWifiIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x19, 0x98, 0x21, 0x84, 0x47, 0xE2, 0x09, 0x90,
  0x11, 0x88, 0x02, 0x40, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char DisplayManager::mqttIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x06, 0x60, 0x0C, 0x20, 0x08, 0x10, 0x38, 0x1C,
  0x60, 0x46, 0x42, 0xE2, 0x42, 0xE2, 0x22, 0x44, 0x1A, 0x58, 0x02, 0x40, 0x07, 0x40, 0x02, 0x00
};
const unsigned char DisplayManager::noMqttIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x06, 0x60, 0x0C, 0x20, 0x08, 0x10, 0x38, 0x1C,
  0x60, 0x04, 0x40, 0x00, 0x40, 0x26, 0x20, 0x1C, 0x1F, 0xD8, 0x00, 0x34, 0x00, 0x22, 0x00, 0x00
};
