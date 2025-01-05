#include <Arduino.h>
#include <ArduinoJson.h>
#include "Lora.h"

// #define _DEBUG

Lora lora;

void setup() {
  //  文字化けする場合は速度を変える
  Serial.begin(115200);

  #ifdef _DEBUG
    Serial.println("setup");
  #endif

  lora.init(0x1111, 0x0001, 5);

  delay(1000);

  JsonDocument doc;
  doc["type"] = "request";
  doc["dst"] = "11110002";
  doc["data_type"] = "temperature";
  String output;
  serializeJson(doc, output);

  lora.send((byte*)output.c_str(), output.length(), 0x1111, 0x0002);
}

void loop() {
  lora.receive();
}
