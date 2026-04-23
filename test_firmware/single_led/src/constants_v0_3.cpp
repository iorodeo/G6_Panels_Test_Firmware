#include "constants.h"

// Hardware revision v0.3 (RP2354A04)
// LED polarity is correct: COL driven high to turn on, ROW driven low.
// 8MB PSRAM is attached with CS on GPIO47.

const uint8_t CS_PIN = 41;

const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN
{20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};

const uint8_t COL_ON_LEVEL = 1;
const uint8_t ROW_ON_LEVEL = 0;
