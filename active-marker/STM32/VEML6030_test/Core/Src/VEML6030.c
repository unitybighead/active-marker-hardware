/*
 * VEML6030.c
 *
 *  Created on: 2024/05/23
 *      Author: NIIMI Haru
 */
#include "VEML6030.h"

static I2C_HandleTypeDef* hi2c;

/*
 * @brief initialize VEML6030
 * @param sensor address
 * @return error
 */
uint8_t VEML6030_init(I2C_HandleTypeDef* p_hi2c,uint8_t addr) {
  hi2c = p_hi2c;
  uint8_t buf[] = { 0x00, 0x00};
  return HAL_I2C_Master_Transmit(hi2c, addr, buf, 2, 100);
}

/*
 * @brief get lux data
 * @param sensor address
 * @return lux
 */
float VEML6030_getLux(uint8_t addr) {
  float gain = VEML6030_getGain(addr);
  uint16_t inttime = VEML6030_getIntTime(addr);
  uint16_t als = VEML6030_getALS(addr);
  float resolution = (1.8432 / ((float) inttime / 25.0)) * (0.125 / gain);
  return als * resolution;
}

/*
 * @brief get gain data
 * @param addr sensor address
 * @return gain
 */
float VEML6030_getGain(uint8_t addr) {
  uint16_t config = VEML6030_readWord(addr, CONF_CMD);
  uint16_t x0 = VEML6030_readBit(config, 11);
  uint16_t x1 = VEML6030_readBit(config, 12);
  float gain = pow(2,(x0 - 3 * x1));
  return gain;
}

/*
 * @brief get cycle time in sensor
 * @param addr sensor address
 * @return cycle time
 */
uint16_t VEML6030_getIntTime(uint8_t addr) {
  uint16_t config = VEML6030_readWord(addr, CONF_CMD);
  uint8_t x2x1 = (config >> 6) & 0x03;
  uint8_t x3 = VEML6030_readBit(config, 8);
  uint8_t x4 = VEML6030_readBit(config, 9);
  uint16_t IntTime = 100 *pow(2,x2x1)/ pow(2,(x3 + x4));
  return IntTime;
}

/*
 * @brief get row illuminance data
 * @param addr address
 * @return row data
 */
uint16_t VEML6030_getALS(uint8_t addr){
  uint16_t als = VEML6030_readWord(addr, ALS_CMD);
  return als;
}

/*
 * @brief read 1 word (2 bytes) from I2C bus
 * @param1 addr address
 * @param2 command read resister's address
 * @return data(Serialized)
 */
uint16_t VEML6030_readWord(uint8_t addr, uint8_t command) {
  uint8_t buf[2] = { };
  HAL_I2C_Mem_Read(hi2c, addr, command, sizeof(uint8_t), buf, 2, 100);
  uint16_t data = (buf[1] << 8) + buf[0];
  return data;
}

/*
 * @brief read 1 bit
 * @param1 data
 * @param2 position of bit you want to read
 */
uint8_t VEML6030_readBit(uint16_t data, uint8_t pos) {
  return (data >> pos) & 0x01;
}
