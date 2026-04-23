#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>
#include <array>

constexpr uint8_t PANEL_SIZE = 20;
constexpr uint8_t NUM_COLOR = 4;

struct BoardConfig {
    uint8_t cs_pin;
    std::array<uint8_t, PANEL_SIZE> col_pins;
    std::array<uint8_t, PANEL_SIZE> row_pins;
    bool col_on_level;
    bool row_on_level;
};

extern const BoardConfig BOARD_CONFIG;

#endif
