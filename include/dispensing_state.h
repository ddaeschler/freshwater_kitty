#ifndef FWK_DISPENSING_STATE_H
#define FWK_DISPENSING_STATE_H

#include <Arduino.h>
#include "state.h"

namespace fwk {
    constexpr unsigned long MINIMUM_DISPENSING_TIME_MS = 5000;
    constexpr unsigned long MAXIMUM_DISPENSING_TIME_MS = 10000;

    /* 
     * Dispense water for a minimum amount of time.
     * This is to ensure the cat gets enough water.
     */
    class DispensingState : public State {
    public:
        DispensingState();
        void enter(unsigned long now) override;
        StateTransition tick(uint8_t radarValue, unsigned long now) override;
    };
}



#endif // FWK_DISPENSING_STATE_H