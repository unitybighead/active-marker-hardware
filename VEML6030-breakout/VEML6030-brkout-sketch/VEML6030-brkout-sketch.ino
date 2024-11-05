/**
 * @file VEML6030-brkout-sketch.ino
 * @brief VEML6030 testing program with M5StickC
 * @author NIIMI Haru
 * @date 2024/05/21
 */

#include <M5StickC.h>
#include "VEML6030.h"
#include "VEML6030-brkout-sketch.h"
#include "active_marker_udp.h"

#define CTRL_CYCLE 1000
#define SENSOR_ADDR 0x48


void CycleController(void) {
  static unsigned long old_time;
  while (millis() - old_time < CTRL_CYCLE)
    ;
  old_time = millis();
}

void M5setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  // M5.Lcd.setTextColor(TFT_WHITE); //bug
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextFont(2);
}

void lcd_print(uint8_t cursor, String str) {
  M5.Lcd.setCursor(0, cursor);
  M5.Lcd.print(str);
}

VEML6030 VEML;

void setup() {
  M5setup();
  udp_setup();
  if (VEML.begin(SENSOR_ADDR, 0, 26)) {
    lcd_print(20, "I2C setup error!");
  }
  lcd_print(0, "Illuminance Sensor");
  lcd_print(40, "Illuminance [lx]");
}

void loop() {
  M5.update();
  //VEML.AutoRange();
  CycleController();
  M5.Lcd.setCursor(0, 60);
  float lux = VEML.GetLux();
  M5.Lcd.printf("%4.2f\n", lux);

  uint8_t lux_data[2] = { 0 };
  lux_data[0] = (uint8_t)((uint16_t)lux & 0xFF);
  lux_data[1] = (uint8_t)(((uint16_t)lux >> 8) & 0xFF);
  udp_array_write(sizeof(lux_data), lux_data);

  if (M5.BtnA.pressedFor(300)) {
    //reboot after one second;
    M5.Lcd.setCursor(100, 60);
    M5.Lcd.printf("Reset");
    esp_deep_sleep(500);
  }
}
