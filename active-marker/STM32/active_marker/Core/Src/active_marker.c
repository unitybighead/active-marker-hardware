/*
 * active_marker.c
 *
 *  Created on: 2024/06/05
 *      Author: harub
 */
#include "active_marker.h"

const RGB COLOR_BLUE = { 0, 0, 255 };
const RGB COLOR_YELLOW = { 255, 255, 0 };
const RGB COLOR_PINK = { 255, 0, 0 };
const RGB COLOR_GREEN = { 0, 255, 0 };

const DotPattern PATTERN_0 = { COLOR_PINK, COLOR_GREEN, COLOR_PINK, COLOR_PINK };
const DotPattern PATTERN_1 =
    { COLOR_GREEN, COLOR_GREEN, COLOR_PINK, COLOR_PINK };
const DotPattern PATTERN_2 =
    { COLOR_GREEN, COLOR_GREEN, COLOR_PINK, COLOR_GREEN };
const DotPattern PATTERN_3 =
    { COLOR_PINK, COLOR_GREEN, COLOR_PINK, COLOR_GREEN };
const DotPattern PATTERN_4 = { COLOR_PINK, COLOR_PINK, COLOR_GREEN, COLOR_PINK };
const DotPattern PATTERN_5 =
    { COLOR_GREEN, COLOR_PINK, COLOR_GREEN, COLOR_PINK };
const DotPattern PATTERN_6 =
    { COLOR_GREEN, COLOR_PINK, COLOR_GREEN, COLOR_GREEN };
const DotPattern PATTERN_7 =
    { COLOR_PINK, COLOR_PINK, COLOR_GREEN, COLOR_GREEN };
const DotPattern PATTERN_8 = { COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
    COLOR_GREEN };
const DotPattern PATTERN_9 = { COLOR_PINK, COLOR_PINK, COLOR_PINK, COLOR_PINK };
const DotPattern PATTERN_10 =
    { COLOR_PINK, COLOR_GREEN, COLOR_GREEN, COLOR_PINK };
const DotPattern PATTERN_11 =
    { COLOR_GREEN, COLOR_PINK, COLOR_PINK, COLOR_GREEN };
const DotPattern PATTERN_12 = { COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
    COLOR_PINK };
const DotPattern PATTERN_13 =
    { COLOR_GREEN, COLOR_PINK, COLOR_PINK, COLOR_PINK };
const DotPattern PATTERN_14 = { COLOR_PINK, COLOR_GREEN, COLOR_GREEN,
    COLOR_GREEN };
const DotPattern PATTERN_15 =
    { COLOR_PINK, COLOR_PINK, COLOR_PINK, COLOR_GREEN };

const DotPattern *PATTERN_ADDR[16] = { &PATTERN_0, &PATTERN_1, &PATTERN_2,
    &PATTERN_3, &PATTERN_4, &PATTERN_5, &PATTERN_6, &PATTERN_7, &PATTERN_8,
    &PATTERN_9, &PATTERN_10, &PATTERN_11, &PATTERN_12, &PATTERN_13, &PATTERN_14,
    &PATTERN_15 };

bool getMode(void) {
  return HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
}

uint8_t getID_Rotary(void) {
  uint8_t ID = 0;
  ID |= !(HAL_GPIO_ReadPin(ID1_GPIO_Port, ID1_Pin)) << 0;
  ID |= !(HAL_GPIO_ReadPin(ID2_GPIO_Port, ID2_Pin)) << 1;
  ID |= !(HAL_GPIO_ReadPin(ID4_GPIO_Port, ID4_Pin)) << 2;
  ID |= !(HAL_GPIO_ReadPin(ID8_GPIO_Port, ID8_Pin)) << 3;
  return ID;
}

uint8_t getColor(void) {
  return HAL_GPIO_ReadPin(COLOR_GPIO_Port, COLOR_Pin);
}


/* 0     4
 *    2
 *  1   3
 */
void setPattern(uint8_t ID, uint8_t color) {
  RGB pattern[5];
  pattern[0] = PATTERN_ADDR[ID]->dot0;
  pattern[1] = PATTERN_ADDR[ID]->dot1;
  pattern[3] = PATTERN_ADDR[ID]->dot2;
  pattern[4] = PATTERN_ADDR[ID]->dot3;
  if (color == BLUE) {
    pattern[2] = COLOR_BLUE;
  } else {
    pattern[2] = COLOR_YELLOW;
  }
  NeoPixel_Send(pattern);
}
