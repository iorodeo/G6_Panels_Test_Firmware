# G6\_Panels\_Test\_Firmware
Some test firmware for the G6 Panels.

## Getting Started

The only prerequisite is [pixi](https://pixi.sh). Once pixi is installed, it manages all other dependencies (including PlatformIO) automatically. This works on **Windows, macOS, and Linux** with no platform-specific setup required.

Each firmware variant is built for a specific hardware revision. Pick the command that matches both the firmware you want and the panel in front of you:

```
pixi run deploy-single-led-v0.1
pixi run deploy-single-led-v0.2
pixi run deploy-single-led-v0.3
```

Lights up a single LED on the panel.

```
pixi run deploy-pattern-v0.1
pixi run deploy-pattern-v0.2
pixi run deploy-pattern-v0.3
```

Displays a static pattern. Each active LED is time-division multiplexed with a fixed 50 µs slot, so the total cycle time grows with the number of active LEDs. Fewer active LEDs means a shorter cycle and brighter appearance; more active LEDs means a longer cycle and dimmer appearance.

```
pixi run deploy-dot-v0.1
pixi run deploy-dot-v0.2
pixi run deploy-dot-v0.3
```

Shows one LED at a time in a bottom-up serpentine scan. The first row scanned is the physical bottom row from left to right; the next row is scanned right to left, and so on until all 400 pixels have been shown exactly once. `dot.cpp` defines a single top-level `PANEL_SCAN_SECONDS` constant, set to `6.0` by default, so each pixel stays on for `6 s / 400 = 15 ms`.

```
pixi run deploy-led-check-v0.1
pixi run deploy-led-check-v0.2
pixi run deploy-led-check-v0.3
```

Drives every LED on the panel fully on for 500 ms, then fully off for 500 ms, while printing `on` / `off` to serial. Useful as a wiring sanity check.

```
pixi run deploy-minimal-v0.1
pixi run deploy-minimal-v0.2
pixi run deploy-minimal-v0.3
```

Revision-agnostic liveness probe. During startup it briefly blinks only the first configured row; once `loop()` is running it toggles the configured column GPIO bank and row GPIO bank in opposite phases at 2 Hz. If the MCU is executing user code at all, every LED on any revision should blink in one phase or the other regardless of LED polarity. Use the command that matches the panel revision so PlatformIO applies the right board profile and pin map while flashing.

## Hardware revisions

| Rev  | Silicon     | CS_PIN | COL_PIN        | ROW_PIN             | LED polarity |
|------|-------------|--------|----------------|---------------------|--------------|
| v0.1 | RP2354A02   | 33     | 1..20          | 21..31, 36..44      | inverted     |
| v0.2 | RP2354A04   | 33     | 1..20          | 21..31, 36..44      | correct      |
| v0.3 | RP2354A04   | 41     | 0..19          | 20..39              | correct (PSRAM on GPIO47) |

v0.1 has the LED polarity inverted compared to v0.2 and v0.3. The firmware accounts for this automatically — just flash the env that matches your board.

## Project Structure

All firmware variants live under `test_firmware/single_led/`. Source files are split by role:

- `src/apps/`: one entrypoint per firmware behavior (`single_led.cpp`, `pattern.cpp`, `dot.cpp`, `led_check.cpp`, `minimal.cpp`)
- `src/board/`: shared `BoardConfig` selected by the PlatformIO hardware profile via `-DPANEL_HW_REV=<n>`
- `src/common/`: shared panel I/O helpers and schematic/layout mapping

Each revision-specific PlatformIO environment is still named `<behavior>_<revision>` (for example `pattern_v0_2`), but board selection now happens through build flags instead of swapping in revision-specific source files.

## License
MIT
