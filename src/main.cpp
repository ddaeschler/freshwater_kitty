#include <Arduino.h>

#include "hardware.h"
#include "state_machine.h"


fwk::StateMachine stateMachine;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(fwk::RADAR_PIN, INPUT);
    pinMode(fwk::SOLENOID_PIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(fwk::SOLENOID_PIN, LOW);
    Serial.begin(57600);
    Serial.println(F("Freshwater Kitty ready"));
}

void loop() {
    stateMachine.tick(digitalRead(fwk::RADAR_PIN), millis());
}
