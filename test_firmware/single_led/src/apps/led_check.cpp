#include <Streaming.h>

#include "board/board_config.h"
#include "common/panel.h"

static uint64_t col_mask = 0;
static uint64_t row_mask = 0;

namespace {

void write_mask_level(uint64_t mask, bool level) {
    if (level) {
        gpio_set_mask64(mask);
    } else {
        gpio_clr_mask64(mask);
    }
}

void set_panel_state(bool on) {
    write_mask_level(col_mask, on ? BOARD_CONFIG.col_on_level : !BOARD_CONFIG.col_on_level);
    write_mask_level(row_mask, on ? BOARD_CONFIG.row_on_level : !BOARD_CONFIG.row_on_level);
}

}  // namespace

void setup() {
    // Serial.begin(115200);
    panel_init_pins();

    for (const uint8_t pin : BOARD_CONFIG.col_pins) {
        col_mask |= (uint64_t(1) << pin);
    }
    for (const uint8_t pin : BOARD_CONFIG.row_pins) {
        row_mask |= (uint64_t(1) << pin);
    }
}

void loop() {
    static uint32_t count = 0;

    set_panel_state(true);
    Serial << "on:  " << count << endl;
    delay(500);

    set_panel_state(false);
    Serial << "off: " << count << endl;
    delay(500);
    count++;
}
