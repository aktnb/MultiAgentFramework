#include <Arduino.h>
#include "Lora.h"
#include "MyMessageHandler.h"

// #define _DEBUG

Lora lora;
MyMessageHandler handler;

void setup() {
  //  文字化けする場合は速度を変える
  Serial.begin(115200);

  #ifdef _DEBUG
    Serial.println("setup");
  #endif

  lora.init(0x1111, 0x0002, 5);
  lora.addHandler(handler);

  delay(1000);
}

void loop() {
  lora.tick();
  handler.tick();
}
