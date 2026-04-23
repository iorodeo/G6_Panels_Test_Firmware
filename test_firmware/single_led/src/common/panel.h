#ifndef PANEL_H
#define PANEL_H

#include <Arduino.h>

// Initializes every row and column GPIO as an output driven to its off level.
void panel_init_pins();

// Drives the LED at the given row/column pin intersection on or off.
void panel_set_pixel(uint8_t row_pin, uint8_t col_pin, bool on);

#endif
