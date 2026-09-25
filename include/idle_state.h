#ifndef FWK_IDLE_STATE_H
#define FWK_IDLE_STATE_H

#include <Arduino.h>
#include "state.h"

namespace fwk {
    /* 
     * Idle state is the initial system state. Nothing is yet detected and the 
     * solenoid is off. The system will transition to the debounce_on_wait state
     * when a cat is detected by the radar sensor.
     */
    class IdleState : public State {
    public:
        IdleState();
        void enter(unsigned long now) override;
        StateTransition tick(uint8_t radarValue, unsigned long now) override;
    };
}



#endif // FWK_IDLE_STATE_H