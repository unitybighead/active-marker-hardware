/*
 * neopixel_spi.c
 *
 *  Created on: May 31, 2024
 *      Author: harub
 */
#include "neopixel_spi.h"

SPI_HandleTypeDef *hspi;

void NeoPixel_Init(SPI_HandleTypeDef *p_hspi) {
  hspi = p_hspi;
}

void NeoPixel_FullOff() {
  // reset: >= 80 us
  RGB RGBbuf[N];
  for (int i = 0; i < N; i++) {
    RGBbuf[i].r = 0;
    RGBbuf[i].g = 0;
    RGBbuf[i].b = 0;
  }
  NeoPixel_Send(RGBbuf);
}

void NeoPixel_FullBright() {
  RGB RGB_buf[N];
  for (int i = 0; i < N; i++) {
    RGB_buf[i].r = 255;
    RGB_buf[i].g = 255;
    RGB_buf[i].b = 255;
  }
  NeoPixel_Send(RGB_buf);
}

void NeoPixel_Send(RGB* RGB_buf) {

  uint8_t *send_buf = (uint8_t*) calloc(N * 24, sizeof(uint8_t));
  NeoPixel_Serialize(RGB_buf, send_buf);
  NeoPixel_Reset();
  if(HAL_SPI_Transmit_DMA(hspi, send_buf, N * 24)!= HAL_OK){
    Error_Handler();
  }
  free(send_buf);
}

void NeoPixel_Reset() {
  uint8_t buf = NP_RESET;
  for (int i = 0; i < 100; i++) {
    HAL_SPI_Transmit_DMA(hspi, &buf, 1);
  }
}

void NeoPixel_Serialize(RGB RGB[], uint8_t buf[]) {
  for (int n = 0; n < N; n++) {
    for (int i = 0; i < 8; i++) {
      if (RGB[n].g & (1 << (7 - i))) {
        buf[n * 24 + i] = NP_HIGH;
      } else {
        buf[n * 24 + i] = NP_LOW;
      }
      if (RGB[n].r & (1 << (7 - i))) {
        buf[n * 24 + i + 8] = NP_HIGH;
      } else {
        buf[n * 24 + i + 8] = NP_LOW;
      }
      if (RGB[n].b & (1 << (7 - i))) {
        buf[n * 24 + i + 16] = NP_HIGH;
      } else {
        buf[n * 24 + i + 16] = NP_LOW;
      }
    }
  }
}
