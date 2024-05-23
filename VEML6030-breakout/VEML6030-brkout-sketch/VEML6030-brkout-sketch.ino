/**
 * @file VEML6030-brkout-sketch.ino
 * @brief VEML6030 testing program with M5StickC
 * @author NIIMI Haru
 * @date 2024/05/21
 */

#include <M5StickC.h>
#include "VEML6030.h"

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

VEML6030 VEML;

void setup() {
  M5setup();
  if (VEML.begin(SENSOR_ADDR, 0, 26)) {
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.println("I2C setup error!");
  }

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("VEML6030 Tester");
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.printf("Illuminance [lx]");
}

void loop() {
  M5.update();
  //VEML.AutoRange();
  CycleController();
  M5.Lcd.setCursor(0, 50);
  float lux = VEML.GetLux();
  M5.Lcd.printf("%4.2f\n", lux);
  if (M5.BtnA.pressedFor(1000)) {
    //reboot after one second;
    M5.Lcd.printf("Reset");
    esp_deep_sleep(500);
  }
}
