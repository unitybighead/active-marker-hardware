#include <WiFi.h>
#include <WiFiUDP.h>
#include <M5StickC.h>

#include "VEML6030-brkout-sketch.h"

#define UDP_TIMEOUT 10000

const char ssid[] = "Finch";     //WiFIのSSIDを入力
const char pass[] = "04240424";  // WiFiのパスワードを入力

WiFiUDP wifiUdp;
const char* pc_addr = "172.20.10.13";  //"192.168.0.6";
const int pc_port = 50007;             //送信先のポート
const int my_port = 50008;             //自身のポート

static bool udp_enable = false;
void udp_setup() {
  int i = 0;
  int delay_time = 10;
  WiFi.begin(ssid, pass);
  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      wifiUdp.begin(my_port);
      M5.Lcd.setCursor(0, 20);
      M5.Lcd.print("IP Addr: ");
      M5.Lcd.print(WiFi.localIP());
      break;
    }
    delay(delay_time);
    i++;
    if (i > UDP_TIMEOUT / delay_time) {
      M5.Lcd.setCursor(0, 20);
      M5.Lcd.print("wifi error");
      break;
    }
  }
}

bool udp_is_enable() {
  return udp_enable;
}

void udp_array_write(int size, uint8_t* data) {
  if (!udp_is_enable()) {
    return;
  }
  wifiUdp.beginPacket(pc_addr, pc_port);
  for (int i = 0; i < size; i++) {
    wifiUdp.write(data[i]);
  }
  wifiUdp.endPacket();
}
