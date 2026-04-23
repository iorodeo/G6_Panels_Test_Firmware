#ifndef PANEL_H
#define PANEL_H

#include <Arduino.h>

void panel_init_pins();
void panel_set_pixel(uint8_t row_pin, uint8_t col_pin, bool on);

#endif
