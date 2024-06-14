/*
 * neopixel_spi.h
 *
 *  Created on: May 31, 2024
 *      Author: harub
 */

#ifndef INC_NEOPIXEL_SPI_H_
#define INC_NEOPIXEL_SPI_H_

#include <malloc.h>
#include "main.h"
/*
 * SPI      6.5 MHz
 * DataSize 8 Bits
 *          0.154 us/bit
 *          1.23 us / Data
 * T0H      0.3 us
 * T0L      0.9 us
 * T1H      0.6 us
 * T1L      0.6 us
 * (+-0.15 us for each)
*/

#define NP_HIGH 0b11110000
#define NP_LOW 0b11000000
#define NP_RESET 0b00000000
#define N 1

typedef struct{
  uint8_t r;
  uint8_t g;
  uint8_t b;
}RGB;

void NeoPixel_Init(SPI_HandleTypeDef* p_hspi);
void NeoPixel_Reset();
void NeoPixel_FullBright();
void NeoPixel_FullOff();
void NeoPixel_Send(RGB RGB_buf[]);
void NeoPixel_Serialize(RGB RGB[],uint8_t buf[]);

#endif /* INC_NEOPIXEL_SPI_H_ */
