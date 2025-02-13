#include "secrets.h"
#include "network_tools.h"
#include "telegram.h"
#include "gate_control.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("\nBooting...");

  // Wi-Fi setup
  bool isWiFiConnected = WiFiClientSetup(WIFI_SSID, WIFI_PASSWORD);
  if (!isWiFiConnected) {
    Serial.println("Wi-Fi connection failed! Restarting...");
    ESP.restart();
  }
  WiFiClientSecure& client = WiFiClientGet();

  // Telegram setup
  TgSetup(client, TG_BOT_TOKEN, TG_ADMIN_CHAT_ID, TG_KNOWN_CHAT_IDS_ARRAY, GateControlOpen);

  // Gate control setup
  GateControlSetup();
}

unsigned long lastCheckTime = 0;
const unsigned long CHECK_INTERVAL = 30 * 1000; // 30 seconds

void loop() {
  // Check connection every 30 seconds
  if (millis() - lastCheckTime > CHECK_INTERVAL) {
    lastCheckTime = millis();
    if (!TgBot.checkConnection()) {
      Serial.println("Internet is unavailable.");
      // reset the board if no internet connection
      Serial.println("Restarting...");
      ESP.restart();
    } else {
      Serial.println("Internet is available.");
    }
  }
  TgCheckNewMessages();
}
