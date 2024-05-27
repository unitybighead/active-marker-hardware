/*
 * VEML6030.h
 *
 *  Created on: 2024/05/23
 *      Author: NIIMI Haru
 */

#ifndef INC_VEML6030_H_
#define INC_VEML6030_H_

#include "main.h"

//Commands
#define CONF_CMD 0x00
#define WINDOW_H_CMD 0x01
#define WINDOW_L_CMD 0x02
#define PWR_CMD 0x03
#define ALS_CMD 0x04
#define WHITE_CMD 0x05
#define INT_CMD 0x06

//Integration Times bit masks
#define IT25 0x300  //25ms
#define IT50 0x200  //50ms
#define IT100 0x000 //100ms
#define IT200 0x040 //200ms
#define IT400 0x080 //400ms
#define IT800 0x0C0 //800ms

#define GAIN_1 0x0000 //Gain x1
#define GAIN_2 0x0800 //Gain x2
#define GAIN_1_8 0x1000 //Gain x1/8
#define GAIN_1_4 0x1800 //Gain x1/4

//Persistance will define how man consecutive values required to trigger interrupt
#define PER_1 0x00 //Persistance of 1
#define PER_2 0x10 //Persistance of 2
#define PER_4 0x20 //Persistance of 4
#define PER_8 0x30 //Persistance of 8

// the device address must be shift 1 bit to left
#define SENS_ADDR_0 0x48 << 1
#define SENS_ADDR_1 0x10 << 1
float VEML6030_getGain(uint8_t addr);
uint8_t VEML6030_init(I2C_HandleTypeDef* p_hi2c,uint8_t addr);
float VEML6030_getLux(uint8_t addr);
uint16_t VEML6030_getIntTime(uint8_t addr);
uint16_t VEML6030_getALS(uint8_t addr);
int VEML6030_readWord(uint8_t addr, uint8_t command);
uint8_t VEML6030_readBit(uint16_t data, uint8_t pos);

#endif /* INC_VEML6030_H_ */
