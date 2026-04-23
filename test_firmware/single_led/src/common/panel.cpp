#include "common/panel.h"

#include "board/board_config.h"

// Configures every panel row/column pin as an output driven to the off state.
void panel_init_pins() {
    uint64_t col_mask = 0;
    for (const uint8_t pin : BOARD_CONFIG.col_pins) {
        gpio_init(pin);
        col_mask |= (uint64_t(1) << pin);
    }
    gpio_set_dir_out_masked64(col_mask);
    if (BOARD_CONFIG.col_on_level) {
        gpio_clr_mask64(col_mask);
    } else {
        gpio_set_mask64(col_mask);
    }

    uint64_t row_mask = 0;
    for (const uint8_t pin : BOARD_CONFIG.row_pins) {
        gpio_init(pin);
        row_mask |= (uint64_t(1) << pin);
    }
    gpio_set_dir_out_masked64(row_mask);
    if (BOARD_CONFIG.row_on_level) {
        gpio_clr_mask64(row_mask);
    } else {
        gpio_set_mask64(row_mask);
    }
}

// Drives one LED intersection according to the board's active polarity levels.
void panel_set_pixel(uint8_t row_pin, uint8_t col_pin, bool on) {
    gpio_put(col_pin, on ? BOARD_CONFIG.col_on_level : !BOARD_CONFIG.col_on_level);
    gpio_put(row_pin, on ? BOARD_CONFIG.row_on_level : !BOARD_CONFIG.row_on_level);
}
