#include "debounce_on_wait_state.h"

#include "hardware.h"

namespace fwk {
    DebounceOnWaitState::DebounceOnWaitState() : State() {

    }

    StateTransition DebounceOnWaitState::tick(uint8_t radarValue, unsigned long now) {
        if (now - stateEnteredAt >= DEBOUNCE_ON_WAIT_INTERVAL_MS) {
            if (radarValue == HIGH) {
                Serial.println(F("Kitty still detected after debounce interval!"));
                return StateTransition::Dispensing;
            } else {
                Serial.println(F("False positive. No kitty detected after debounce interval."));
                return StateTransition::Idle;
            }
        }

        return StateTransition::None;
    }

    void DebounceOnWaitState::enter(unsigned long now) {
        stateEnteredAt = now;
        Serial.println(F("Debouncing kitty detection."));
        syncHardwareToState(LOW);
    }
}