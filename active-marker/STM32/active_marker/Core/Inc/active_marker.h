/*
 * active_marker.h
 *
 *  Created on: 2024/06/05
 *      Author: harub
 */

#ifndef INC_ACTIVE_MARKER_H_
#define INC_ACTIVE_MARKER_H_

#include <string.h>
#include "main.h"
#include "neopixel_spi.h"

#define BLUE 0
#define YELLOW 1
#define MODE_MEMORY 0
#define MODE_UART 1

typedef struct {
  RGB *dot0;
  RGB *dot1;
  RGB *dot2;
  RGB *dot3;
} DotPattern;

enum Uart_command {
  COMMAND_BLUE,
  COMMAND_YELLOW,
  COMMAND_PINK,
  COMMAND_GREEN,
  COMMAND_ILLUMINANCE,
  COMMAND_ID
};


uint8_t getID(void);
int getMode(void);
uint8_t getColor(void);
void setPattern(uint8_t ID, uint8_t color);

void Uart_Init(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart_arg);

#endif /* INC_ACTIVE_MARKER_H_ */
