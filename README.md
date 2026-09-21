# freshwater_kitty
Arduino project to detect kitty and flow fresh water into a basin

Dedicated to Mkit for all her love and support

## Development

The default target is an Arduino Uno (ATmega328P), using the Arduino framework
and PlatformIO's `atmelavr` platform. If your board is a different ATmega model,
change the `board` setting in `platformio.ini` to its
[PlatformIO board ID](https://docs.platformio.org/en/latest/platforms/atmelavr.html#boards).

Install the PlatformIO IDE extension for VS Code, or install
[PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html)
for command-line development. Run these commands from the project directory
(or the PlatformIO terminal in VS Code):

```sh
pio run                     # Build firmware
pio run --target upload     # Upload to a connected board
pio device monitor          # Open serial monitor at 115200 baud
```

PlatformIO downloads the AVR toolchain and Arduino framework on the first build.
If port detection fails, pass `--upload-port /dev/ttyACM0` when uploading or
`--port /dev/ttyACM0` when opening the monitor, using your board's actual port.

The starter firmware in `src/main.cpp` prints `Freshwater Kitty ready` at startup
and toggles the built-in LED every 500 ms without blocking the main loop.
Kitty detection and water control are still to be implemented.

Project headers belong in `include/`, private libraries in `lib/`, and future
unit tests in `test/`.
