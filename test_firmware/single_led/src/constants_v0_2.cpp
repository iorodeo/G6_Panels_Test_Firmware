#include "constants.h"

// Hardware revision v0.2 (RP2354A04)
// LED polarity is correct: COL driven high to turn on, ROW driven low.

const uint8_t CS_PIN = 33;

const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN
{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN
{21,22,23,24,25,26,27,28,29,30,31,36,37,38,39,40,41,42,43,44};

const uint8_t COL_ON_LEVEL = 1;
const uint8_t ROW_ON_LEVEL = 0;
