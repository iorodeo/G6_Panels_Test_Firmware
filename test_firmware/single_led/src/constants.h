#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>
#include <ArduinoEigen.h>

constexpr uint8_t  PANEL_SIZE = 20;
constexpr uint8_t  NUM_COLOR = 4;

extern const uint8_t CS_PIN; 
extern const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN; 
extern const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN;

#endif

