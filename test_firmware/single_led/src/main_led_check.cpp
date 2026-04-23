#include <Streaming.h>
#include "constants.h"
#include "utilities.h"

static uint64_t col_mask = 0;
static uint64_t row_mask = 0;

void setup() {
    Serial.begin(115200);
    panel_init_pins();

    for (size_t i = 0; i < COL_PIN.size(); i++) {
        col_mask |= (uint64_t(1) << COL_PIN(i));
    }
    for (size_t i = 0; i < ROW_PIN.size(); i++) {
        row_mask |= (uint64_t(1) << ROW_PIN(i));
    }
}


void loop() {
    static uint32_t count = 0;

    // All pixels ON
    if (COL_ON_LEVEL) gpio_set_mask64(col_mask); else gpio_clr_mask64(col_mask);
    if (ROW_ON_LEVEL) gpio_set_mask64(row_mask); else gpio_clr_mask64(row_mask);
    Serial << "on:  " << count << endl;
    delay(500);

    // All pixels OFF
    if (COL_ON_LEVEL) gpio_clr_mask64(col_mask); else gpio_set_mask64(col_mask);
    if (ROW_ON_LEVEL) gpio_clr_mask64(row_mask); else gpio_set_mask64(row_mask);
    Serial << "off: " << count << endl;
    delay(500);
    count++;
}
