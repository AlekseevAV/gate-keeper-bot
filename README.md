# Gate Keeper Bot

An Arduino-based project for controlling gates remotely via a Telegram bot. This project uses an ESP32 
microcontroller to integrate network connectivity and automated gate management with a Telegram-based user interface.

---

## Features

- **Remote Control**: Open and close gates via Telegram commands.
- **Network Tools**: Built-in internet connectivity checks and retries.
- **Secure Access**: Restrict commands to authorized Telegram users.
- **Ping/DNS Checks**: Monitor internet availability with customizable intervals and retries.

---

## Prerequisites

### Hardware
- ESP32 Development Board

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
- Libraries (install via Arduino Library Manager):
   - [WiFi](https://github.com/espressif/arduino-esp32)
   - [AsyncTelegram2](https://github.com/AlekseevAV/gate-keeper-bot.git)

---

## File Structure

```
gate_keeper_bot/
├── gate_keeper_bot.ino        # Main sketch file
├── gate_control.h             # Functions for gate operations
├── network_tools.h            # Internet connectivity tools
├── telegram.h                 # Telegram bot logic
└── secrets.h                  # Configuration for sensitive data (excluded from the repository)
```

---

## Installation

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/your-username/gate-keeper-bot.git
    cd gate-keeper-bot
    ```

2. **Set up Secrets**:
    Create a file secrets.h from the template provided in secrets.example.h.

3. Install Required Libraries:

    Open Arduino IDE and navigate to:

    ```
    Sketch -> Include Library -> Manage Libraries...
    ```

    Install:
    * WiFi
    * AsyncTelegram2

4. Upload the Code:
    * Connect your ESP32 to your computer via USB.
    * Select the correct board:

    ```
    Tools -> Board -> ESP32 Dev Module
    ```

    * Select the correct port:

    ```
    Tools -> Port -> <Your ESP32 Port>
    ```

    * Upload the code to the ESP32.


## Telegram Commands

Command	Description

* /start - Initialize the bot
* /open - Open the gate

Example Telegram Setup
1. Create a Telegram bot using BotFather and retrieve your bot token.
2. Add your Telegram chat ID to TG_ADMIN_CHAT_ID in secrets.h.
3. Authorize additional users by adding their chat IDs to the TG_KNOWN_CHAT_IDS_ARRAY.

# Troubleshooting

* Wi-Fi Not Connecting:
    * Check your Wi-Fi credentials in secrets.h.
    * Ensure the ESP32 is within range of the Wi-Fi network.
* Telegram Bot Not Responding:
    * Verify that the bot token is correct in secrets.h.
    * Check the bot’s permissions in Telegram (e.g., ensure it can receive messages).
* Internet Unavailable:
    * Debug connectivity using the serial monitor.
    * Use the checkInternetWithDNS function to verify internet access.

# Contributing

Contributions are welcome! If you’d like to contribute, please fork the repository and submit a pull request.

# License

This project is licensed under the MIT License. See the LICENSE file for details.
