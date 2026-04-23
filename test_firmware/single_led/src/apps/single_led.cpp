#include "board/board_config.h"
#include "common/layout_map.h"
#include "common/panel.h"

// Initializes the panel GPIOs for the selected hardware revision.
void setup() {
    panel_init_pins();
}

// Repeatedly strobes the LED at layout coordinate (0, 0).
void loop() {
    static const Index led_index{0, 0};
    static const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_index);
    static const uint8_t row = BOARD_CONFIG.row_pins[led_sch_index.first];
    static const uint8_t col = BOARD_CONFIG.col_pins[led_sch_index.second];

    panel_set_pixel(row, col, true);
    delayMicroseconds(10);
    panel_set_pixel(row, col, false);
    delayMicroseconds(40);
}
