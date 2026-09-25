#include "hardware.h"

namespace fwk {
    void syncHardwareToState(uint8_t radarValue) {
        digitalWrite(LED_BUILTIN, radarValue);
        digitalWrite(SOLENOID_PIN, radarValue);
    }
}