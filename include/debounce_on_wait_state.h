#ifndef FWK_DEBOUNCE_ON_WAIT_STATE_H
#define FWK_DEBOUNCE_ON_WAIT_STATE_H

#include <Arduino.h>
#include "state.h"

namespace fwk {
    constexpr unsigned long DEBOUNCE_ON_WAIT_INTERVAL_MS = 5000;

    /* 
     * Debounce turning the fountain on unless the rader sensor is still high 
     * after a debounce interval. This is to avoid false positives from the 
     * radar sensor.
     */
    class DebounceOnWaitState : public State {
    public:
        DebounceOnWaitState();
        void enter(unsigned long now) override;
        StateTransition tick(uint8_t radarValue, unsigned long now) override;
    };
}



#endif // FWK_IDLE_STATE_H