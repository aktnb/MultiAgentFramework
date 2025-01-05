#include <Arduino.h>
#include "Lora.h"

// #define _DEBUG

Lora lora;

void setup() {
  //  文字化けする場合は速度を変える
  Serial.begin(115200);

  #ifdef _DEBUG
    Serial.println("setup");
  #endif

  lora.init(0x1111, 0x0002, 5);

  delay(1000);
}

void loop() {
  lora.receive();
}
