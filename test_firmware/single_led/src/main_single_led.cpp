#include "constants.h"
#include "utilities.h"

void setup() {

    // If you want to use usb/serial communications
    //Serial.begin(115200);

    // Initialize col pins, create mask and set to low
    uint64_t COL_PIN_mask = 0;
    for (size_t i=0; i<COL_PIN.size(); i++) {
        gpio_init(COL_PIN(i));
        COL_PIN_mask |= (uint64_t(1) << COL_PIN(i));
    }
    gpio_set_dir_out_masked64(COL_PIN_mask);
    gpio_set_mask64(COL_PIN_mask);

    // Initialize row pins, create mask and set to high
    uint64_t ROW_PIN_mask = 0;
    for (size_t i=0; i<ROW_PIN.size(); i++) {
        gpio_init(ROW_PIN(i));
        ROW_PIN_mask |= (uint64_t(1) << ROW_PIN(i));
    }
    gpio_set_dir_out_masked64(ROW_PIN_mask);
    gpio_clr_mask64(ROW_PIN_mask);

}


void loop() {

    static const Index led_index {0,0};   // index of led in physical layout
    static const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_index);
    static const uint8_t row = ROW_PIN[led_sch_index.first];
    static const uint8_t col = COL_PIN[led_sch_index.second];

    // Turn led on
    gpio_put(col,1);
    gpio_put(row,0);
    delayMicroseconds(10);

    // Turn led off
    gpio_put(col,0);
    gpio_put(row,1);
    delayMicroseconds(40);
}
