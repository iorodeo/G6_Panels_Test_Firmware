#include "common/layout_map.h"

namespace {

Index convert_schematic_to_layout(Index schem_ind) {
    Index layout_ind;
    if (schem_ind.second % NUM_COLOR < NUM_COLOR / 2) {
        if (schem_ind.first < PANEL_SIZE / 2) {
            layout_ind.first = 2 * schem_ind.first;
            layout_ind.second = schem_ind.second;
        } else {
            layout_ind.first = 2 * (PANEL_SIZE - (schem_ind.first + 1));
            layout_ind.second = NUM_COLOR / 2 + schem_ind.second;
        }
    } else {
        if (schem_ind.first < PANEL_SIZE / 2) {
            layout_ind.first = 2 * schem_ind.first + 1;
            layout_ind.second = schem_ind.second - NUM_COLOR / 2;
        } else {
            layout_ind.first = 2 * (PANEL_SIZE - (schem_ind.first + 1)) + 1;
            layout_ind.second = schem_ind.second;
        }
    }
    return layout_ind;
}

IndexMap create_schematic_to_layout_map() {
    IndexMap map;
    for (uint8_t i = 0; i < PANEL_SIZE; i++) {
        for (uint8_t j = 0; j < PANEL_SIZE; j++) {
            Index schem_ind{i, j};
            Index layout_ind = convert_schematic_to_layout(schem_ind);
            map.insert({schem_ind, layout_ind});
        }
    }
    return map;
}

IndexMap create_layout_to_schematic_map() {
    IndexMap map;
    for (uint8_t i = 0; i < PANEL_SIZE; i++) {
        for (uint8_t j = 0; j < PANEL_SIZE; j++) {
            Index schem_ind{i, j};
            Index layout_ind = convert_schematic_to_layout(schem_ind);
            map.insert({layout_ind, schem_ind});
        }
    }
    return map;
}

}  // namespace

const IndexMap SCHEMATIC_TO_LAYOUT_MAP = create_schematic_to_layout_map();
const IndexMap LAYOUT_TO_SCHEMATIC_MAP = create_layout_to_schematic_map();
