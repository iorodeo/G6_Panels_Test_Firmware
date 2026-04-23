#include "constants.h"
#include "utilities.h"

void setup() {
    panel_init_pins();
}


void loop() {

    static const Index led_index {0,0};   // index of led in physical layout
    static const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_index);
    static const uint8_t row = ROW_PIN[led_sch_index.first];
    static const uint8_t col = COL_PIN[led_sch_index.second];

    panel_set_pixel(row, col, true);
    delayMicroseconds(10);
    panel_set_pixel(row, col, false);
    delayMicroseconds(40);
}
