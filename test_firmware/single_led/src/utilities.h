#ifndef UTILITIES_H 
#define UTILITIES_H
#include <map>
#include <Arduino.h>
#include "constants.h"

// Led array index type
using Index = std::pair<uint8_t, uint8_t>;
using IndexMap = std::map<Index, Index>;

// Maps for converting between schematic and layout indices
extern IndexMap SCHEMATIC_TO_LAYOUT_MAP;
extern IndexMap LAYOUT_TO_SCHEMATIC_MAP;

// Initialize all COL_PIN and ROW_PIN lines as outputs driven to the "off"
// level for the current hardware revision (determined by COL_ON_LEVEL and
// ROW_ON_LEVEL in constants.h).
void panel_init_pins();

// Drive a single (row_pin, col_pin) pair so that the LED at their
// intersection is on or off, respecting the revision's polarity.
void panel_set_pixel(uint8_t row_pin, uint8_t col_pin, bool on);

#endif

