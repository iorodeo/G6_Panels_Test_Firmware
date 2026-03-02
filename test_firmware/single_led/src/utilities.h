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

#endif

