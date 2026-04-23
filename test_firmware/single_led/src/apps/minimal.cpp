//
// Minimal liveness probe.
//
// Drives GPIO0..19 and GPIO20..39 in opposite phases at ~2 Hz. No Serial, no
// TinyUSB-dependent calls. If the chip executes user code at all, every LED on
// the panel should blink in one phase or the other regardless of driver polarity.
//
// The pre_setup_blink constructor runs BEFORE the Arduino framework calls
// setup() — it pulses GPIO0 twice. If the MCU is alive but TinyUSB init hangs
// later, we still see those two pulses at boot.
//
#include <Arduino.h>
#include "hardware/gpio.h"

static uint64_t col_mask = 0;
static uint64_t row_mask = 0;

__attribute__((constructor))
// Emits a visible boot pulse before Arduino or TinyUSB setup begins.
static void pre_setup_blink() {
    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);
    for (int i = 0; i < 4; ++i) {
        gpio_put(0, 1);
        busy_wait_us(100000);
        gpio_put(0, 0);
        busy_wait_us(100000);
    }
}

// Configures GPIO0..39 as two output banks used by the liveness probe.
void setup() {
    for (uint8_t p = 0; p <= 19; ++p) {
        gpio_init(p);
        gpio_set_dir(p, GPIO_OUT);
        col_mask |= (uint64_t(1) << p);
    }
    for (uint8_t p = 20; p <= 39; ++p) {
        gpio_init(p);
        gpio_set_dir(p, GPIO_OUT);
        row_mask |= (uint64_t(1) << p);
    }
}

// Alternates the two GPIO banks so every LED blinks in one phase or the other.
void loop() {
    gpio_set_mask64(col_mask);
    gpio_clr_mask64(row_mask);
    delay(250);
    gpio_clr_mask64(col_mask);
    gpio_set_mask64(row_mask);
    delay(250);
}
