#include "state_machine.h"

namespace fwk {
    StateMachine::StateMachine() : idleState_(), debounceOnWaitState_(), dispensingState_(), offWaitState_(), currentState_(&idleState_) {
        currentState_->enter(millis());
    }

    void StateMachine::tick(uint8_t radarValue, unsigned long now) {
        StateTransition transition = currentState_->tick(radarValue, now);
        if (transition != StateTransition::None) {
            transitionToState(transition, now);
        }
    }

    void StateMachine::transitionToState(StateTransition transition, unsigned long now) {
        switch (transition) {
            case StateTransition::Idle:
                currentState_ = &idleState_;
                break;
            case StateTransition::DebounceOnWait:
                currentState_ = &debounceOnWaitState_;
                break;
            case StateTransition::Dispensing:
                currentState_ = &dispensingState_;
                break;
            case StateTransition::OffWait:
                currentState_ = &offWaitState_;
                break;
            default:
                Serial.println(F("Invalid state transition."));
                return;
        }
        currentState_->enter(now);
    }
}