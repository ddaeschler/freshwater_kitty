#include <Arduino.h>

namespace {

constexpr uint8_t RADAR_PIN = 2;
constexpr uint8_t SOLENOID_PIN = 7;
constexpr unsigned long DEBOUNCE_INTERVAL_MS = 5000;
unsigned long lastEdgeAt = 0;
uint8_t lastEdgeRadarValue = LOW;
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RADAR_PIN, INPUT);
    pinMode(SOLENOID_PIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(SOLENOID_PIN, LOW);
    Serial.begin(57600);
    Serial.println(F("Freshwater Kitty ready"));
}

void syncHardwareToState(uint8_t radarValue, unsigned long now = millis()) {
    lastEdgeAt = now;
    lastEdgeRadarValue = radarValue;
    digitalWrite(LED_BUILTIN, radarValue);
    digitalWrite(SOLENOID_PIN, radarValue);
}

void loop() {
    const uint8_t radarValue = digitalRead(RADAR_PIN);
    const unsigned long now = millis();

    // debounce only the shutoff edge, not the trigger edge, to avoid
    // delays when the cat walks in front of the radar sensor.

    if (radarValue == HIGH && lastEdgeRadarValue == LOW) {
        Serial.println(F("Kitty detected!"));
        syncHardwareToState(radarValue, now);
    }
    else if (radarValue == LOW && lastEdgeRadarValue == HIGH) {
        if (now - lastEdgeAt > DEBOUNCE_INTERVAL_MS) {
            Serial.println(F("Kitty gone!"));
            syncHardwareToState(radarValue, now);
        }
    }
}
