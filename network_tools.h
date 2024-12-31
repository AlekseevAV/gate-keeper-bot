#ifndef INTERNET_CHECK_H
#define INTERNET_CHECK_H

#include <WiFi.h>
#include <WiFiClientSecure.h>

// Wi-Fi parameters
const unsigned long WIFI_TIMEOUT = 15000; // (ms) Timeout for Wi-Fi connection

// Parameters for internet checking
const char* pingHost = "google.com";
unsigned long lastCheckTime = 0; // Tracks the last time we checked internet
unsigned int failedAttempts = 0; // Counts consecutive failed attempts
const unsigned long checkInterval = 5000; // Interval between checks (ms)
const unsigned int maxFailedAttempts = 3; // Maximum allowed failed attempts

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

bool checkInternetConnection() {
  if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi not connected!");
      return false;
  }

  IPAddress resolvedIP;
  if (WiFi.hostByName(pingHost, resolvedIP)) {
      Serial.print("DNS lookup succeeded: ");
      Serial.println(resolvedIP);
      return true;
  } else {
      Serial.println("DNS lookup failed!");
      return false;
  }
}

bool checkInternetWithRetry() {
  unsigned long currentTime = millis();

  // Perform the check only if the interval has passed
  if (currentTime - lastCheckTime < checkInterval) {
    return true; // Assume availability during the interval
  }
  lastCheckTime = currentTime;

  // Perform the actual internet check
  if (checkInternetConnection()) {
    Serial.println("Internet is available.");
    failedAttempts = 0; // Reset failed attempts counter
    return true;
  } else {
    failedAttempts++;
    Serial.print("Failed attempt: ");
    Serial.println(failedAttempts);
  }

  // Return false if failed attempts exceed the maximum
  if (failedAttempts >= maxFailedAttempts) {
    Serial.println("Maximum failed attempts reached. Internet unavailable.");
    return false;
  }

  return true; // Internet might still be available if under the limit
}

#endif // INTERNET_CHECK_H
