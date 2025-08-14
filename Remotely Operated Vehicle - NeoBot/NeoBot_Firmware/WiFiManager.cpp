#include "WiFiManager.h"

/**
 * Constructor - can be expanded for debug setup or callbacks later.
 */
WiFiManager::WiFiManager() {
  // Nothing needed for now
}

/**
 * Begin WiFi connection.
 * If ssid/password are nullptr, use default values.
 */
void WiFiManager::begin(const char* ssid, const char* password) {
  const char* connect_ssid = ssid ? ssid : default_ssid;
  const char* connect_pass = password ? password : default_password;

  Serial.println("[WiFiManager] Connecting to WiFi...");
  WiFi.begin(connect_ssid, connect_pass);

  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 15000;  // 15 seconds

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFiManager] Connected!");
    Serial.print("[WiFiManager] IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n[WiFiManager] Failed to connect to WiFi.");
  }
}

/**
 * Return connection status.
 */
bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

/**
 * Attempt reconnection if not connected.
 */
void WiFiManager::reconnectIfNeeded() {
  if (!isConnected()) {
    Serial.println("[WiFiManager] WiFi disconnected. Reconnecting...");
    WiFi.reconnect();
  }
}
