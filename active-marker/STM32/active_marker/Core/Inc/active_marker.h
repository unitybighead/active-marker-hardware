/*
 * active_marker.h
 *
 *  Created on: 2024/06/05
 *      Author: harub
 */

#ifndef INC_ACTIVE_MARKER_H_
#define INC_ACTIVE_MARKER_H_

#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "neopixel_spi.h"

#define TEAM_COLOR_BLUE true
#define TEAM_COLOR_YELLOW false
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t getID(void);
int getMode(void);
bool getColor(void);
void setIDSwitch(void);
void setColorSwitch(void);
void setPattern(uint8_t ID, uint8_t color);

void Uart_Init(UART_HandleTypeDef *huart);
void Uart_checkReset();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart_arg);

#endif /* INC_ACTIVE_MARKER_H_ */
