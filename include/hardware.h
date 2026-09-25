#ifndef FWK_HARDWARE_H
#define FWK_HARDWARE_H

#include <Arduino.h>

namespace fwk {
    constexpr uint8_t RADAR_PIN = 2;
    constexpr uint8_t SOLENOID_PIN = 7;

    void syncHardwareToState(uint8_t radarValue);
}

#endif // FWK_HARDWARE_H