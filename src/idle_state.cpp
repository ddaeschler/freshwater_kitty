#include "idle_state.h"

#include "hardware.h"

namespace fwk {
    IdleState::IdleState() : State() {

    }

    StateTransition IdleState::tick(uint8_t radarValue, unsigned long now) {
        if (radarValue == HIGH) {
            // Kitty detected! Transition to debounce_on_wait state.
            return StateTransition::DebounceOnWait;
        }
        
        return StateTransition::None;
    }

    void IdleState::enter(unsigned long now) {
        stateEnteredAt = now;
        Serial.println(F("No kitty. Entering Idle state."));
        syncHardwareToState(LOW);
    }
}