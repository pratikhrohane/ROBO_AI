#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

/**
 * WiFiManager class handles Wi-Fi connection logic for ESP32.
 * 
 * Features:
 * - Easy setup with hardcoded or runtime credentials
 * - Auto-reconnect logic
 * - Debug output
 */
class WiFiManager {
public:
  // Constructor
  WiFiManager();

  /**
     * Initialize WiFi with given SSID and password.
     * If empty, fallback to hardcoded values.
     */
  void begin(const char* ssid = nullptr, const char* password = nullptr);

  /**
     * Check if ESP32 is connected to WiFi.
     */
  bool isConnected();

  /**
     * Attempt to reconnect to WiFi if disconnected.
     */
  void reconnectIfNeeded();

private:
  const char* default_ssid = "YOUR_DEFAULT_SSID";          // fallback SSID
  const char* default_password = "YOUR_DEFAULT_PASSWORD";  // fallback password
};

#endif  // WIFI_MANAGER_H
