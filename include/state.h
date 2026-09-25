#ifndef FWK_STATE_H
#define FWK_STATE_H

#include <Arduino.h>
#include "state_transition.h"

namespace fwk {
    /*
     * Base class for all states. Each state is responsible for handling the
     * radar sensor input and controlling the solenoid output. The state machine
     * will transition between states based on the radar sensor input and various
     * timing constraints. Each state will implement the tick(millis) method to 
     * handle the radar sensor input and control the solenoid output.
     */
    class State {
    protected:
        unsigned long stateEnteredAt = 0;
    public:
        State();
        virtual void enter(unsigned long now) = 0;
        virtual StateTransition tick(uint8_t radarValue, unsigned long now) = 0;
        virtual ~State() = default;
    };
}

#endif // FWK_STATE_H