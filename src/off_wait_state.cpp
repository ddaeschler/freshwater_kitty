#include "off_wait_state.h"

#include "hardware.h"

namespace fwk {
    OffWaitState::OffWaitState() : State() {

    }

    StateTransition OffWaitState::tick(uint8_t radarValue, unsigned long now) {
        if (now - stateEnteredAt >= OFF_WAIT_INTERVAL_MS) {
            return StateTransition::Idle;
        }
        
        return StateTransition::None;
    }

    void OffWaitState::enter(unsigned long now) {
        stateEnteredAt = now;
        Serial.println(F("Waiting before allowing fountain to sense again."));
        syncHardwareToState(LOW);
    }
}