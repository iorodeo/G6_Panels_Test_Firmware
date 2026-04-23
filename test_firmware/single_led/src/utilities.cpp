#include "utilities.h"

// Converts given schematic index to layout indices
Index convert_schematic_to_layout(Index schem_ind) {
    Index layout_ind;
    if (schem_ind.second % NUM_COLOR < NUM_COLOR/2) {
        if (schem_ind.first < PANEL_SIZE/2) {
            layout_ind.first = 2*schem_ind.first;
            layout_ind.second = schem_ind.second;
        }
        else {
            layout_ind.first = 2*(PANEL_SIZE - (schem_ind.first+1));
            layout_ind.second = NUM_COLOR/2 + schem_ind.second;
        }
    }
    else {
        if (schem_ind.first < PANEL_SIZE/2) {
            layout_ind.first = 2*schem_ind.first + 1;
            layout_ind.second = schem_ind.second - NUM_COLOR/2;
        }
        else {
            layout_ind.first = 2*(PANEL_SIZE - (schem_ind.first+1)) + 1;
            layout_ind.second = schem_ind.second;
        }
    }
    return layout_ind;
}

// Get map for converting from schematic to layout indices
IndexMap create_schematic_to_layout_map() {
    IndexMap map;
    for (uint8_t i=0; i<PANEL_SIZE; i++) {
        for (uint8_t j=0; j<PANEL_SIZE; j++) {
            Index schem_ind {i,j};
            Index layout_ind = convert_schematic_to_layout(schem_ind);
            map.insert({schem_ind, layout_ind});
        }
    }
    return map;
}

// Get map for converting from layout to schematic indices 
IndexMap create_layout_to_schematic_map() {
    IndexMap map;
    for (uint8_t i=0; i<PANEL_SIZE; i++) {
        for (uint8_t j=0; j<PANEL_SIZE; j++) {
            Index schem_ind {i,j};
            Index layout_ind = convert_schematic_to_layout(schem_ind);
            map.insert({layout_ind, schem_ind});
        }
    }
    return map;
}

IndexMap SCHEMATIC_TO_LAYOUT_MAP = create_schematic_to_layout_map();
IndexMap LAYOUT_TO_SCHEMATIC_MAP = create_layout_to_schematic_map();

void panel_init_pins() {
    uint64_t col_mask = 0;
    for (size_t i = 0; i < COL_PIN.size(); i++) {
        gpio_init(COL_PIN(i));
        col_mask |= (uint64_t(1) << COL_PIN(i));
    }
    gpio_set_dir_out_masked64(col_mask);
    if (COL_ON_LEVEL) gpio_clr_mask64(col_mask);
    else              gpio_set_mask64(col_mask);

    uint64_t row_mask = 0;
    for (size_t i = 0; i < ROW_PIN.size(); i++) {
        gpio_init(ROW_PIN(i));
        row_mask |= (uint64_t(1) << ROW_PIN(i));
    }
    gpio_set_dir_out_masked64(row_mask);
    if (ROW_ON_LEVEL) gpio_clr_mask64(row_mask);
    else              gpio_set_mask64(row_mask);
}

void panel_set_pixel(uint8_t row_pin, uint8_t col_pin, bool on) {
    gpio_put(col_pin, on ? COL_ON_LEVEL : !COL_ON_LEVEL);
    gpio_put(row_pin, on ? ROW_ON_LEVEL : !ROW_ON_LEVEL);
}
