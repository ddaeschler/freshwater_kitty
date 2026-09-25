#ifndef FWK_STATE_MACHINE_H
#define FWK_STATE_MACHINE_H

#include "state_transition.h"
#include "state.h"
#include "idle_state.h"
#include "debounce_on_wait_state.h"
#include "dispensing_state.h"
#include "off_wait_state.h"

namespace fwk {
    class StateMachine {
    public:
        StateMachine();
        void tick(uint8_t radarValue, unsigned long now);

    private:
        IdleState idleState_;
        DebounceOnWaitState debounceOnWaitState_;
        DispensingState dispensingState_;
        OffWaitState offWaitState_;    

        State* currentState_;

        void transitionToState(StateTransition transition, unsigned long now);
    };
}

#endif // FWK_STATE_MACHINE_H