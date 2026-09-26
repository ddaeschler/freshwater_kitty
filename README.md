# freshwater_kitty
An Arduino-controlled fresh-water dispenser that detects a cat with a radar
sensor and opens a solenoid valve to flow water into a basin.

Dedicated to Mkit for all her love and support

![Mkit the cat](mkit.jpg)

## How it works

The main loop in [`src/main.cpp`](src/main.cpp) passes the radar sensor's digital
presence reading and `millis()` to the [state machine](src/state_machine.cpp).
Each state controls the valve and built-in LED together, using nonblocking timers:

| State | Valve and LED | Transition |
| --- | --- | --- |
| `Idle` | Off | A HIGH radar reading starts `DebounceOnWait`. |
| `DebounceOnWait` | Off | After five seconds, a HIGH reading starts `Dispensing`; a LOW reading returns to `Idle`. |
| `Dispensing` | On | A LOW reading ends dispensing after at least five seconds. At ten seconds, dispensing ends regardless of the radar reading. Both paths return to `Idle`. |

At startup, the system is idle with the valve and LED off. The initial five-second
wait checks presence when the interval expires; LOW readings during the wait
neither cancel nor restart its timer. Dispensing timers start when the valve opens.

An `OffWait` state is also implemented to hold the valve off for five seconds
before returning to `Idle`, but is currently unused. There is no
separate forced cooldown after dispensing. With continuous HIGH input, the system
dispenses for ten seconds, returns to `Idle`, and goes through the five-second
detection wait again before reopening the valve.

Serial output at **57600 baud** prints `Freshwater Kitty ready` at startup and
reports state entries, detection confirmation or rejection, and the reason
dispensing ended.

## Hardware

The [electrical schematic](docs_design/electrical.pdf) documents an Arduino Uno,
LD2410C radar sensor module, solenoid valve, MT3608 boost converter set to 12 V,
and an IRLZ44N MOSFET valve driver. The driver includes a 100 Ω gate resistor,
10 kΩ gate pulldown, and 1N4001 flyback diode; the supply includes a 470 µF capacitor.

| Connection | Arduino pin | Behavior |
| --- | --- | --- |
| Radar sensor OUT | D2 (input) | HIGH indicates presence |
| Valve driver gate, through 100 Ω resistor | D7 (output) | HIGH energizes the valve |
| Built-in LED | `LED_BUILTIN` | Mirrors the valve output |

The schematic uses a shared 5 V supply for the Arduino, radar sensor, and boost
converter input, with a common ground. The valve is powered by the 12 V boost
output and switched through the MOSFET driver.

The [physical design notes](docs_design/physical.pdf) describe the reservoir and
basin arrangement, tubing, and estimated water flow trajectory.

## Configuration

The pin assignments (`RADAR_PIN`, `SOLENOID_PIN`) are defined in
[`include/hardware.h`](include/hardware.h). Timing constants are in the state headers:

| Constant | Default | Header |
| --- | --- | --- |
| `DEBOUNCE_ON_WAIT_INTERVAL_MS` | 5000 ms | [debounce_on_wait_state.h](include/debounce_on_wait_state.h) |
| `MINIMUM_DISPENSING_TIME_MS` | 5000 ms | [dispensing_state.h](include/dispensing_state.h) |
| `MAXIMUM_DISPENSING_TIME_MS` | 10000 ms | [dispensing_state.h](include/dispensing_state.h) |
| `OFF_WAIT_INTERVAL_MS` | 5000 ms (currently unused state) | [off_wait_state.h](include/off_wait_state.h) |

Serial speed is set in both `Serial.begin()` and `platformio.ini`; keep these
values matched when changing it.

## Development

The default target is an Arduino Uno (ATmega328P), using the Arduino framework,
PlatformIO's `atmelavr` platform, and GNU C++17. If your board is a different ATmega model,
change the `board` setting in `platformio.ini` to its
[PlatformIO board ID](https://docs.platformio.org/en/latest/platforms/atmelavr.html#boards).

Install the PlatformIO IDE extension for VS Code, or install
[PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html)
for command-line development. Run these commands from the project directory
(or the PlatformIO terminal in VS Code):

```sh
pio run                     # Build firmware
pio run --target upload     # Upload to a connected board
pio device monitor          # Open serial monitor at 57600 baud
```

PlatformIO downloads the AVR toolchain and Arduino framework on the first build.
If port detection fails, pass `--upload-port /dev/ttyACM0` when uploading or
`--port /dev/ttyACM0` when opening the monitor, using your board's actual port.

After uploading, open the serial monitor and reset the board to see the startup
message. Check the following behavior against the radar's digital output:

1. Trigger detection. The valve and LED stay off for five seconds, then turn on
   if the radar is still HIGH when the wait expires.
2. Try a brief detection with the radar LOW when the wait expires. The system
   returns to idle without opening the valve.
3. During dispensing, clear detection before five seconds have elapsed. The
   valve stays on until the minimum dispensing time, then closes if the radar is LOW.
4. Keep detection HIGH. The valve closes after ten seconds and remains off during
   the next five-second detection wait before dispensing again.

The serial messages report the state transitions and dispensing stop conditions.

Project headers belong in `include/`, private libraries in `lib/`, and future
unit tests in `test/`. No automated tests are included yet.
