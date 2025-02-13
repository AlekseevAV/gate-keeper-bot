#ifndef INTERNET_CHECK_H
#define INTERNET_CHECK_H

#include <WiFi.h>
#include <WiFiClientSecure.h>

// Wi-Fi parameters
const unsigned long WIFI_TIMEOUT = 15000; // (ms) Timeout for Wi-Fi connection

// Define the Wi-Fi client
WiFiClientSecure client;

// Function to connect to Wi-Fi
bool WiFiClientSetup(const char* ssid, const char* password) {
  Serial.print("Connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  time_t start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - start > WIFI_TIMEOUT) {
      Serial.println("Wi-Fi connection timeout!");
      return false;
    }
  }
  Serial.println("\nConnected to Wi-Fi! IP address: ");
  Serial.println(WiFi.localIP());

  return true;
}

WiFiClientSecure& WiFiClientGet() {
  return client;
}

#endif // INTERNET_CHECK_H
