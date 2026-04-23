#include "board/board_config.h"

#ifndef PANEL_HW_REV
#error "PANEL_HW_REV must be defined by the PlatformIO environment."
#endif

namespace {

constexpr BoardConfig make_board_config() {
#if PANEL_HW_REV == 1
    return {33,
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 36, 37, 38, 39, 40, 41, 42, 43, 44},
            false,
            true};
#elif PANEL_HW_REV == 2
    return {33,
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 36, 37, 38, 39, 40, 41, 42, 43, 44},
            true,
            false};
#elif PANEL_HW_REV == 3
    return {41,
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
            {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
            true,
            false};
#else
#error "Unsupported PANEL_HW_REV value."
#endif
}

}  // namespace

const BoardConfig BOARD_CONFIG = make_board_config();
