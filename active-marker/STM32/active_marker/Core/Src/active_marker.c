/*
 * active_marker.c
 *
 *  Created on: 2024/06/05
 *      Author: harub
 */
#include "active_marker.h"
#include <core_cm4.h>

static RGB color_blue = { 0, 0, 255 };
static RGB color_yellow = { 255, 255, 0 };
static RGB color_pink = { 255, 0, 0 };
static RGB color_green = { 0, 255, 0 };

/*color define {R,G,B}
 * 0     3
 *
 *  1   2
 */

static const DotPattern PATTERN_0 = { &color_pink, &color_green, &color_pink,
    &color_pink };
static const DotPattern PATTERN_1 = { &color_green, &color_green, &color_pink,
    &color_pink };
static const DotPattern PATTERN_2 = { &color_green, &color_green, &color_pink,
    &color_green };
static const DotPattern PATTERN_3 = { &color_pink, &color_green, &color_pink,
    &color_green };
static const DotPattern PATTERN_4 = { &color_pink, &color_pink, &color_green,
    &color_pink };
static const DotPattern PATTERN_5 = { &color_green, &color_pink, &color_green,
    &color_pink };
static const DotPattern PATTERN_6 = { &color_green, &color_pink, &color_green,
    &color_green };
static const DotPattern PATTERN_7 = { &color_pink, &color_pink, &color_green,
    &color_green };
static const DotPattern PATTERN_8 = { &color_green, &color_green, &color_green,
    &color_green };
static const DotPattern PATTERN_9 = { &color_pink, &color_pink, &color_pink,
    &color_pink };
static const DotPattern PATTERN_10 = { &color_pink, &color_green, &color_green,
    &color_pink };
static const DotPattern PATTERN_11 = { &color_green, &color_pink, &color_pink,
    &color_green };
static const DotPattern PATTERN_12 = { &color_green, &color_green, &color_green,
    &color_pink };
static const DotPattern PATTERN_13 = { &color_green, &color_pink, &color_pink,
    &color_pink };
static const DotPattern PATTERN_14 = { &color_pink, &color_green, &color_green,
    &color_green };
static const DotPattern PATTERN_15 = { &color_pink, &color_pink, &color_pink,
    &color_green };
static const DotPattern PATTERN_16 = { &color_pink, &color_green, &color_blue,
    &color_yellow };

static const DotPattern *PATTERN_ADDR[17] = { &PATTERN_0, &PATTERN_1,
    &PATTERN_2, &PATTERN_3, &PATTERN_4, &PATTERN_5, &PATTERN_6, &PATTERN_7,
    &PATTERN_8, &PATTERN_9, &PATTERN_10, &PATTERN_11, &PATTERN_12, &PATTERN_13,
    &PATTERN_14, &PATTERN_15, &PATTERN_16 };

// UART
static bool uart_first_received = false;
static UART_HandleTypeDef *huart;
static uint8_t rx_buf[8];
static const int msg_size = 8;
static uint8_t ID = 8;
static bool color = TEAM_COLOR_BLUE;
static uint16_t illuminance = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (getMode() == MODE_MEMORY) {
    switch (GPIO_Pin) {
    case ID1_Pin:
    case ID2_Pin:
      setIDSwitch();
      break;

    case COLOR_Pin:
      setColorSwitch();
      break;

    case USER_BTN1_Pin:
      ID++;
      if (ID > 15) {
        ID = 0;
      }
      break;

    case USER_BTN2_Pin:
      color = !color;
      break;

    default:
      break;
    }
  }
}

int getMode(void) {
  return HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
}

uint8_t getID(void) {
  return ID;
}

bool getColor(void) {
  return color;
}

void setIDSwitch(void) {
  // Because of my bad circuit specs......
  ID = 0;
  ID |= !(HAL_GPIO_ReadPin(ID1_GPIO_Port, ID1_Pin)) << 0;
  ID |= !(HAL_GPIO_ReadPin(ID2_GPIO_Port, ID2_Pin)) << 1;
  ID |= !(HAL_GPIO_ReadPin(ID4_GPIO_Port, ID4_Pin)) << 2;
  ID |= !(HAL_GPIO_ReadPin(ID8_GPIO_Port, ID8_Pin)) << 3;
}

void setColorSwitch(void) {
  color = HAL_GPIO_ReadPin(COLOR_GPIO_Port, COLOR_Pin);
}

/* 0     4
 *    2
 *  1   3
 */
void setPattern(uint8_t ID, uint8_t color) {
  RGB pattern[5];
  pattern[0] = *(PATTERN_ADDR[ID]->dot0);
  pattern[1] = *(PATTERN_ADDR[ID]->dot1);
  pattern[3] = *(PATTERN_ADDR[ID]->dot2);
  pattern[4] = *(PATTERN_ADDR[ID]->dot3);
  if (color == TEAM_COLOR_BLUE) {
    pattern[2] = color_blue;
  } else {
    pattern[2] = color_yellow;
  }
  /*
   * Since data transfer to the first LED may fail,
   * the same output process is repeated.
   */
  NeoPixel_Send(pattern);
  HAL_Delay(10);
  NeoPixel_Send(pattern);
}

//--------------------------------------------
// UART

void Uart_Init(UART_HandleTypeDef *huart_arg) {
  huart = huart_arg;
  HAL_UART_Receive_IT(huart, rx_buf, msg_size);
}

void Uart_checkReset() {
  if (getMode() == MODE_UART && !uart_first_received && uwTick > 3000) {
    HAL_NVIC_SystemReset();
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart_arg) {
  if (huart_arg == huart && getMode() == MODE_UART) {
    uart_first_received = true;
    switch (rx_buf[0]) {
    case COMMAND_BLUE:
      color_blue.r = rx_buf[1];
      color_blue.g = rx_buf[2];
      color_blue.b = rx_buf[3];
      break;
    case COMMAND_YELLOW:
      color_yellow.r = rx_buf[1];
      color_yellow.g = rx_buf[2];
      color_yellow.b = rx_buf[3];
      break;
    case COMMAND_PINK:
      color_pink.r = rx_buf[1];
      color_pink.g = rx_buf[2];
      color_pink.b = rx_buf[3];
      break;
    case COMMAND_GREEN:
      color_green.r = rx_buf[1];
      color_green.g = rx_buf[2];
      color_green.b = rx_buf[3];
      break;
    case COMMAND_ILLUMINANCE:
      illuminance = 0;
      illuminance += (rx_buf[1] << 8) + rx_buf[2];
      break;
    case COMMAND_ID:
      ID = rx_buf[1];
      color = rx_buf[2];
      break;
    default:
      break;
    }
  }
  HAL_UART_Receive_IT(huart, rx_buf, msg_size);
}
