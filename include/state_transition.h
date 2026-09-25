#ifndef FWK_STATE_TRANSITION_H
#define FWK_STATE_TRANSITION_H

enum class StateTransition {
    None,
    Idle,
    DebounceOnWait,
    Dispensing,
    OffWait,
};

#endif // FWK_STATE_TRANSITION_H