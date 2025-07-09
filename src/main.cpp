//
//  920MHz LoRa/FSK RF module ES920LR3
//  receive data display on OLED(SSD1306)
//  for ESP32-WROOM-32E
//
//  MaiaR Create 2024/12/14
//

#include <Arduino.h>
#include <Wire.h>
#include "LoRa.h"

void setup()
{
  LoRaInit();
}

int count = 0;
void loop()
{
  Serial.println("Count: " + String(count));
  count++;

  String str;
  // char ss[10];
  char Buf[5];
  if (Serial2.available())
  {
    Serial.println("Serial2 available");
    String rxs = Serial2.readString();
    Serial.print(rxs);

    Serial.println("T: " + rxs.substring(2, 6) + " 'C ");
    /*
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
    Serial.print(" dBm ");*/
  }
  delay(1000);
}
