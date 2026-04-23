#include "constants.h"
#include "utilities.h"

void setup() {
    Serial.begin(115200);
    panel_init_pins();
}

// 20x20 pattern matrix defining which LEDs are on (1) and off (0)
// Rows and columns correspond to physical layout indices
static const Eigen::Matrix<uint8_t, PANEL_SIZE, PANEL_SIZE> pattern =
    (Eigen::Matrix<uint8_t, PANEL_SIZE, PANEL_SIZE>() <<
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
    ).finished();


void loop() {

    // Each active LED (pattern value == 1) is turned on individually for a fixed
    // duration (40 µs on + 10 µs off = 50 µs per LED). The loop scans through the
    // entire 20x20 matrix and only spends time on LEDs that are set to 1, skipping
    // LEDs set to 0. This means:
    //
    //   cycle_time = num_active_leds * 50 µs
    //
    // The more LEDs are on, the longer a single full cycle takes, and consequently
    // the less frequently each individual LED is refreshed. With fewer active LEDs
    // the cycle is shorter and each LED appears brighter because it receives a
    // larger share of the total time. For example:
    //   -   1 LED  on: cycle =   50 µs  (20 000 refreshes/s per LED)
    //   -  10 LEDs on: cycle =  500 µs  ( 2 000 refreshes/s per LED)
    //   - 400 LEDs on: cycle = 20 ms    (    50 refreshes/s per LED)
    //
    // Note: if only a single LED is set to 1 in the pattern matrix, the
    // behaviour is very similar to main_single_led.cpp: one LED toggling
    // on and off at the same duty cycle and refresh rate.

    for (uint8_t row = 0; row < PANEL_SIZE; row++) {
        for (uint8_t col = 0; col < PANEL_SIZE; col++) {
            if (pattern(row, col) == 0) continue;

            const Index led_layout_index = {row, col};
            const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_layout_index);
            const uint8_t row_pin = ROW_PIN[led_sch_index.first];
            const uint8_t col_pin = COL_PIN[led_sch_index.second];

            panel_set_pixel(row_pin, col_pin, true);
            delayMicroseconds(10);
            panel_set_pixel(row_pin, col_pin, false);
            delayMicroseconds(40);
        }
    }
}
