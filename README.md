# G6\_Panels\_Test\_Firmware
Some test firmware for the G6 Panels.

## Getting Started

The only prerequisite is [pixi](https://pixi.sh). Once pixi is installed, it manages all other dependencies (including PlatformIO) automatically. This works on **Windows, macOS, and Linux** with no platform-specific setup required.

To compile and upload a firmware variant to a connected G6 panel, run one of the following commands:

```
pixi run deploy-single-led
```

This lights up a single LED on the panel.

```
pixi run deploy-pattern
```

This displays a static pattern on the panel. Each active LED is time-division multiplexed with a fixed 50 µs slot, so the total cycle time grows with the number of active LEDs. Fewer active LEDs means a shorter cycle and brighter appearance; more active LEDs means a longer cycle and dimmer appearance.

```
pixi run deploy-led-check
```

This checks whether the LEDs on a panel are reversed. It toggles all row pins on and off every 500 ms and prints the current state (`on`/`off`) to serial. If the LEDs light up with this firmware, the panel has reversed LEDs (see [Batch 0.1.3 Hardware](#%EF%B8%8F-batch-013-hardware) below).

Each command will install all dependencies, compile the firmware, and upload it to the G6 panel if it is connected via USB. The same commands work across all platforms.

## ⚠️ Batch 0.1.3 Hardware

The "batch0.1.3" hardware has the LEDs flipped, meaning the high/low signals are reversed compared to the standard design. **This batch may behave unexpectedly and should not be used.** The standard `deploy-single-led` and `deploy-pattern` commands will not work correctly on this hardware.

For debugging purposes, dedicated batch0.1.3 commands are available that account for the reversed polarity:

```
pixi run deploy-single-led-batch0.1.3
```

```
pixi run deploy-pattern-batch0.1.3
```

These will upload firmware with corrected signal levels to the batch0.1.3 hardware.

## Project Structure

All firmware variants — including the reversed-LED check and the batch0.1.3 hacks — are consolidated into a single PlatformIO project under `test_firmware/single_led/`. Each variant is its own PlatformIO environment with a dedicated `main_*.cpp` entry point, while shared code like `constants.cpp` and `utilities.cpp` lives in one place.

In parallel to this consolidation, Will had added standalone examples for the reversed-LED check (`rev_led_check`) and the reversed single-LED hack (`hacks/single_led_with_rev_leds`) to the upstream repository, each in its own separate project directory. Those have since been merged into `test_firmware/single_led/` as well, eliminating the duplicated configuration and source files.

## License
MIT
