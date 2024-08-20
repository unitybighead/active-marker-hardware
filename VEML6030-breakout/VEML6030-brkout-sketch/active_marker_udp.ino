#include <WiFi.h>
#include <WiFiUDP.h>
#include <M5StickC.h>

#include "VEML6030-brkout-sketch.h"

#define UDP_TIMEOUT 100

const char ssid[] = "Finch"; //WiFIのSSIDを入力
const char pass[] = "04240424"; // WiFiのパスワードを入力

WiFiUDP wifiUdp; 
const char *pc_addr = "172.20.10.11";  //"192.168.0.6";
const int pc_port = 50007; //送信先のポート
const int my_port = 50008;  //自身のポート

static bool udp_enable = false;
void udp_setup(){
  int i = 0;
  int delay_time = 10;
  WiFi.begin(ssid,pass);
  while(1){
    if(WiFi.status() != WL_CONNECTED){
      udp_enable = true;
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("IP Address: ");
      M5.Lcd.print(WiFi.localIP());
      wifiUdp.begin(my_port);
      break;
    }
    delay(delay_time);
    i++;
    if(i>UDP_TIMEOUT/delay_time){
      break;
    }
  }
}

bool udp_is_enable(){
  return udp_enable;
}

void udp_array_write(int size,uint8_t* data){
  if(!udp_is_enable()){
    return;
  }
  wifiUdp.beginPacket(pc_addr,pc_port);
  for(int i = 0; i < size; i++){
    wifiUdp.write(data[i]);
  }
  wifiUdp.endPacket();
} 
