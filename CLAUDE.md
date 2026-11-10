# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Busylight is a physical indicator showing whether the owner is in a meeting and whether their mic is open. It is early-stage firmware: currently `src/main.cpp` only connects to WiFi and blinks an LED. Code comments and serial log messages are partly in German.

## Build / flash

PlatformIO project, single environment `seeed_xiao_esp32c3` (ESP32-C3, Arduino framework). There are no tests yet (`test/` holds only the PlatformIO placeholder README).

```bash
pio run                      # build
pio run -t upload            # flash to the connected board
pio device monitor -b 115200 # serial output (Serial.begin(115200))
pio test                     # run unit tests once any exist in test/
```

## Hardware notes

- The XIAO ESP32C3 has no `LED_BUILTIN`; the status LED is an external LED on pin `D10`.

## Firmware structure

- `wifiCredentials[]` is a list of SSID/password pairs. The firmware tries one network; if still not connected after `reconnectInterval` (12 s), `loop()` rotates to the next entry and reconnects. Credentials in the committed source are placeholders (`***`) — keep real passwords out of the repo.
- `loop()` currently uses blocking `delay()` calls for the blink, so the reconnect check only runs about every 2 s. Keep this in mind when adding status/LED logic that needs to be responsive.
