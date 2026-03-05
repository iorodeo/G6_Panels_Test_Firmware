# G6\_Panels\_Test\_Firmware  
Some test firmware for the G6 Panels.

## Getting Started

The only prerequisite is [pixi](https://pixi.sh). Once pixi is installed, it manages all other dependencies (including PlatformIO) automatically. This works on **Windows, macOS, and Linux** and no platform-specific setup required.

To compile and upload a firmware variant to a connected G6 panel, run one of the following commands:

```
pixi run deploy-single-led
```

This lights up a single LED on the panel.

```
pixi run deploy-pattern
```

This displays a static pattern on the panel. Each active LED is time-division multiplexed with a fixed 50 µs slot, so the total cycle time grows with the number of active LEDs. Fewer active LEDs means a shorter cycle and brighter appearance; more active LEDs means a longer cycle and dimmer appearance.

Each command will install all dependencies, compile the firmware, and upload it to the G6 panel if it is connected via USB. The same commands work across all platforms.

## License
MIT
