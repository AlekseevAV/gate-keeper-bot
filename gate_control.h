#ifndef GATE_CONTROL_H
#define GATE_CONTROL_H

#include <Arduino.h>

// Remote PINS
#define POWER_VDD_PIN 12
#define BUTTON_PIN 2


// When the button is pressed, it passes LOW signal to the controller
// So, we keep it LOW by default and just power up the controller
// when we need to press the button (open the gate)
void GateControlOpen() {
  Serial.println("Opening a gate");
  // Power up the remote controller
  digitalWrite(POWER_VDD_PIN, HIGH);
  delay(1000);
  // Power down the remote controller
  digitalWrite(POWER_VDD_PIN, LOW);
  Serial.println("Done");
}

void GateControlSetup() {
  pinMode(POWER_VDD_PIN, OUTPUT);
  digitalWrite(POWER_VDD_PIN, LOW);
  // Keep the button LOW by default
  pinMode(BUTTON_PIN, OUTPUT);
  digitalWrite(BUTTON_PIN, LOW);
}

#endif // !GATE_CONTROL_H
