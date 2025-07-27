//
//  920MHz LoRa/FSK RF module ES920LR3
//  receive data display on OLED(SSD1306)
//  for ESP32-WROOM-32E
//
//  MaiaR Create 2024/12/14
//

#include <Arduino.h>
#include <Wire.h>
#include "es.h"

ES920LR3 lora; // ES920LR3インスタンスを作成

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  } // Wait

  Serial.println("LoRa Receiver");
  if (lora.init())
  {
    Serial.println("LoRa initialization successful");
  }
  else
  {
    Serial.println("LoRa initialization failed");
  }
}

bool first = false;
void loop()
{
	if (!first) Serial.print("Waiting");
  // Serial.print(".");
  first = true;

  // ES920LR3クラスのメソッドを使用してデータ受信をチェック
  if (lora.is_available())
  {
	  first = false;
	  Serial.println("");
    Serial.println("LoRa data available");
    String rxs = lora.receive_data();
    Serial.println("Received: " + rxs);

    // 元のデータ解析処理（コメントアウト解除する場合）
    /*
    char Buf[5];
    rxs.toCharArray(Buf, 5);
    int16_t rssi = abs(strtol(Buf,NULL,16));
    rxs = rxs.substring(4);
    if (rxs.length() > 12){
      Serial.println("T: " + rxs.substring( 2, 6 ) + " 'C " );
      Serial.println("H: " + rxs.substring( 8,12 ) + " % "  );
      if (rxs.length() > 16){
        Serial.println("P: " + rxs.substring(14,18 ) + " hPa ");
      }
    } else {
      Serial.println(rxs);
    }
    Serial.print("R: ");
    Serial.print(rssi);
    Serial.print(" dBm ");
    */
  }
  // delay(1000);
}
