#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <WiFiClientSecure.h>
#include <AsyncTelegram2.h>

#define OPEN_GATE_BUTTON_TEXT  "Open the Gate"
static const char** KNOWN_CHAT_IDS_ARRAY = nullptr;
static const char* ADMIN_CHAT_ID = nullptr;

// Callback function to control the gate
typedef void (*GateControlOpenFunc)();
GateControlOpenFunc gateControlOpen = nullptr;


// reply keyboard object helper
ReplyKeyboard myReplyKbd;
AsyncTelegram2 TgBot(client);

// Handle messages with specific commands
void processCommand(const TBMessage& msg, const String& text) {
  if (text == "/start") {
    String welcome = "Welcome, " + msg.sender.firstName + " " + msg.sender.lastName + ".\n";
    TgBot.sendMessage(msg, welcome);
    TgBot.sendMessage(msg, "This is a reply keyboard:", myReplyKbd);
  } else if (text == "/open" || text == OPEN_GATE_BUTTON_TEXT) {
    if (gateControlOpen) {
      gateControlOpen();
      TgBot.sendMessage(msg, "Opening the gate");
    } else {
      TgBot.sendMessage(msg, "Gate control is not available");
    }
  } else if (text == "/state") {
    TgBot.sendMessage(msg, "Ok");
  } else {
    TgBot.sendMessage(msg, "I don't know what you mean.");
  }
}

// Helper function: Check if a chat ID is authorized
bool isAuthorized(const String& chat_id) {
  for (size_t i = 0; i < sizeof(KNOWN_CHAT_IDS_ARRAY); i++) {
    if (chat_id == KNOWN_CHAT_IDS_ARRAY[i]) {
      return true;
    }
  }
  return false;
}

// Handle incoming messages
void handleNewMessages(TBMessage& msg) {
  String chat_id = String(msg.chatId);
  String text = msg.text;

  Serial.println("New message from " + chat_id + ": " + text);

  if (!isAuthorized(chat_id)) {
    Serial.println("Unauthorized user");
    TgBot.sendMessage(msg, "Unauthorized user");
    TgBot.sendToChannel(ADMIN_CHAT_ID, "Unauthorized access from " + chat_id, true);
    return;
  }

  processCommand(msg, text);
}

void TgSetup(
    WiFiClientSecure& client,
    const char* bot_token,
    const char* admin_chat_id,
    const char* known_chat_ids_array[],
    GateControlOpenFunc gateControlOpenFunc
  ) {
  client.setCACert(telegram_cert);

  KNOWN_CHAT_IDS_ARRAY = known_chat_ids_array;
  ADMIN_CHAT_ID = admin_chat_id;
  gateControlOpen = gateControlOpenFunc;

  // Telegram
  TgBot.setUpdateTime(2000);
  TgBot.setTelegramToken(bot_token);

  // Add sample inline keyboard
  myReplyKbd.addButton(OPEN_GATE_BUTTON_TEXT);
  myReplyKbd.enableResize();

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  TgBot.begin() ? Serial.println("OK") : Serial.println("NOK");
}


void TgCheckNewMessages() {
  TBMessage msg;
  // if there is an incoming message...
  if (TgBot.getNewMessage(msg)) {
    handleNewMessages(msg);
  }
}

#endif // !TELEGRAM_H
