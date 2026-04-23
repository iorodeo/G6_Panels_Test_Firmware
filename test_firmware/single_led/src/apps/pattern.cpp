#include <ArduinoEigen.h>

#include "board/board_config.h"
#include "common/layout_map.h"
#include "common/panel.h"

void setup() {
    Serial.begin(115200);
    panel_init_pins();
}

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
    for (uint8_t row = 0; row < PANEL_SIZE; row++) {
        for (uint8_t col = 0; col < PANEL_SIZE; col++) {
            if (pattern(row, col) == 0) continue;

            const Index led_layout_index = {row, col};
            const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_layout_index);
            const uint8_t row_pin = BOARD_CONFIG.row_pins[led_sch_index.first];
            const uint8_t col_pin = BOARD_CONFIG.col_pins[led_sch_index.second];

            panel_set_pixel(row_pin, col_pin, true);
            delayMicroseconds(10);
            panel_set_pixel(row_pin, col_pin, false);
            delayMicroseconds(40);
        }
    }
}
