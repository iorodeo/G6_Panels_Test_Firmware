#ifndef LAYOUT_MAP_H
#define LAYOUT_MAP_H

#include <cstdint>
#include <map>
#include <utility>

#include "board/board_config.h"

using Index = std::pair<uint8_t, uint8_t>;
using IndexMap = std::map<Index, Index>;

extern const IndexMap SCHEMATIC_TO_LAYOUT_MAP;
extern const IndexMap LAYOUT_TO_SCHEMATIC_MAP;

#endif
