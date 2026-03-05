#include <Streaming.h>
#include "constants.h"

uint64_t COL_PIN_mask = 0;
uint64_t ROW_PIN_mask = 0;

void setup() {

    Serial.begin(115200);  

    // Initialize col pins, create mask and set to low
    for (size_t i=0; i<COL_PIN.size(); i++) {
        gpio_init(COL_PIN(i));
        COL_PIN_mask |= (uint64_t(1) << COL_PIN(i));
    }
    gpio_set_dir_out_masked64(COL_PIN_mask);
    gpio_clr_mask64(COL_PIN_mask);

    // Initialize row pins, create mask and set to low 
    for (size_t i=0; i<ROW_PIN.size(); i++) {
        gpio_init(ROW_PIN(i));
        ROW_PIN_mask |= (uint64_t(1) << ROW_PIN(i));
    }
    gpio_set_dir_out_masked64(ROW_PIN_mask);
    gpio_clr_mask64(ROW_PIN_mask);

}


void loop() {
    static uint32_t count=0;

    // Turn reversed leds on
    gpio_set_mask64(ROW_PIN_mask);
    Serial << "on:  " << count << endl;
    delay(500);

    // Turn reversed leds off
    gpio_clr_mask64(ROW_PIN_mask);
    Serial << "off: " << count << endl;
    delay(500);
    count++;
}


