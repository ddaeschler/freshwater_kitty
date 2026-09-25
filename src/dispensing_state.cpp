#include "dispensing_state.h"

#include "hardware.h"

namespace fwk {
    DispensingState::DispensingState() : State() {

    }

    StateTransition DispensingState::tick(uint8_t radarValue, unsigned long now) {
        if (now - stateEnteredAt >= MINIMUM_DISPENSING_TIME_MS && radarValue == LOW) {
            Serial.println(F("No more kitty detected while dispensing."));
            return StateTransition::Idle;
        }

        if (now - stateEnteredAt >= MAXIMUM_DISPENSING_TIME_MS) {
            Serial.println(F("Maximum dispensing time elapsed."));
            return StateTransition::Idle;
        }
        
        return StateTransition::None;
    }

    void DispensingState::enter(unsigned long now) {
        stateEnteredAt = now;
        Serial.println(F("Dispensing water."));
        syncHardwareToState(HIGH);
    }
}