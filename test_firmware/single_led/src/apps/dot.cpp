#include "board/board_config.h"
#include "common/layout_map.h"
#include "common/panel.h"

constexpr float PANEL_SCAN_SECONDS = 6.0f;
constexpr uint16_t NUM_PIXELS = PANEL_SIZE * PANEL_SIZE;
constexpr uint32_t PIXEL_DWELL_US = static_cast<uint32_t>((PANEL_SCAN_SECONDS * 1000000.0f) / NUM_PIXELS);

static_assert(PIXEL_DWELL_US > 0, "PANEL_SCAN_SECONDS is too short for the panel size.");

namespace {

// Returns the physical layout coordinate for a serpentine scan that starts at
// the bottom-left corner and moves upward row by row.
Index layout_index_from_scan_step(uint16_t scan_step) {
    const uint8_t row_from_bottom = scan_step / PANEL_SIZE;
    const uint8_t col_in_row = scan_step % PANEL_SIZE;
    const uint8_t layout_row = (PANEL_SIZE - 1) - row_from_bottom;
    const bool left_to_right = (row_from_bottom % 2) == 0;
    const uint8_t layout_col = left_to_right ? col_in_row : (PANEL_SIZE - 1) - col_in_row;
    return {layout_row, layout_col};
}

// Waits for the configured per-pixel dwell time derived from PANEL_SCAN_SECONDS.
void delay_pixel_dwell() {
    delay(PIXEL_DWELL_US / 1000);
    delayMicroseconds(PIXEL_DWELL_US % 1000);
}

}  // namespace

// Initializes the panel GPIOs for the selected hardware revision.
void setup() {
    panel_init_pins();
}

// Lights one LED at a time in a bottom-up serpentine scan across the panel.
void loop() {
    static uint16_t scan_step = 0;

    const Index led_layout_index = layout_index_from_scan_step(scan_step);
    const Index led_sch_index = LAYOUT_TO_SCHEMATIC_MAP.at(led_layout_index);
    const uint8_t row_pin = BOARD_CONFIG.row_pins[led_sch_index.first];
    const uint8_t col_pin = BOARD_CONFIG.col_pins[led_sch_index.second];

    panel_set_pixel(row_pin, col_pin, true);
    delay_pixel_dwell();
    panel_set_pixel(row_pin, col_pin, false);

    scan_step = (scan_step + 1) % NUM_PIXELS;
}
