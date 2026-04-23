//
// Minimal liveness probe.
//
// Drives the configured column and row GPIO banks in opposite phases at ~2 Hz.
// No Serial, no TinyUSB-dependent calls. If the chip executes user code at all,
// every LED on the panel should blink in one phase or the other regardless of
// driver polarity.
//
// The pre_setup_blink constructor runs BEFORE the Arduino framework calls
// setup() — it briefly blinks only the first configured row. If the MCU is
// alive but TinyUSB init hangs later, we still see that boot-time activity.
//
#include <Arduino.h>

#include "board/board_config.h"
#include "hardware/gpio.h"

static uint64_t col_mask = 0;
static uint64_t row_mask = 0;

namespace {

// Configures one row/column pin bank as outputs and returns its bitmask.
uint64_t init_output_mask(const std::array<uint8_t, PANEL_SIZE>& pins) {
    uint64_t mask = 0;
    for (const uint8_t pin : pins) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
        mask |= (uint64_t(1) << pin);
    }
    return mask;
}

// Drives every GPIO selected by the bitmask to the requested logic level.
void write_mask_level(uint64_t mask, bool level) {
    if (level) {
        gpio_set_mask64(mask);
    } else {
        gpio_clr_mask64(mask);
    }
}

// Applies one phase of the two-bank probe: one bank high, the other low.
void set_probe_phase(bool col_level, bool row_level) {
    write_mask_level(col_mask, col_level);
    write_mask_level(row_mask, row_level);
}

// Blinks only the first configured row using the revision-specific active
// levels, making the setup-time signal smaller than the full probe pattern.
void set_boot_row_state(bool on) {
    write_mask_level(col_mask, on ? BOARD_CONFIG.col_on_level : !BOARD_CONFIG.col_on_level);
    write_mask_level(row_mask, !BOARD_CONFIG.row_on_level);
    gpio_put(BOARD_CONFIG.row_pins[0], on ? BOARD_CONFIG.row_on_level : !BOARD_CONFIG.row_on_level);
}

}  // namespace

__attribute__((constructor))
// Emits a first-row blink before Arduino or TinyUSB setup begins.
static void pre_setup_blink() {
    col_mask = init_output_mask(BOARD_CONFIG.col_pins);
    row_mask = init_output_mask(BOARD_CONFIG.row_pins);

    for (int i = 0; i < 4; ++i) {
        set_boot_row_state(true);
        busy_wait_us(100000);
        set_boot_row_state(false);
        busy_wait_us(100000);
    }
}

// Configures the revision-specific column and row GPIO banks used by the probe.
void setup() {
    col_mask = init_output_mask(BOARD_CONFIG.col_pins);
    row_mask = init_output_mask(BOARD_CONFIG.row_pins);
}

// Alternates the two GPIO banks so every LED blinks in one phase or the other.
void loop() {
    set_probe_phase(true, false);
    delay(250);
    set_probe_phase(false, true);
    delay(250);
}
