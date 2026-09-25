#ifndef FWK_OFF_WAIT_STATE_H
#define FWK_OFF_WAIT_STATE_H

#include <Arduino.h>
#include "state.h"

namespace fwk {
    constexpr unsigned long OFF_WAIT_INTERVAL_MS = 5000;

    /* 
     * Wait before allowing the fountain to start sensing again.
     * This prevents the radar sensor from triggering on the movement
     * of the water/lines in the fountain after dispensing.
     */
    class OffWaitState : public State {
    public:
        OffWaitState();
        void enter(unsigned long now) override;
        StateTransition tick(uint8_t radarValue, unsigned long now) override;
    };
}



#endif // FWK_OFF_WAIT_STATE_H