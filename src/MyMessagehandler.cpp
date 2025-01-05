#include <Arduino.h>
#include <ArduinoJson.h>
#include "MyMessageHandler.h"
#include "Lora.h"


void MyMessageHandler::init(Lora &lora) {
  this->lora = lora;
}

void MyMessageHandler::onRequest(JsonDocument &doc) {
  Serial.println("Request received");
  String dst = doc["dst"];
  String dataType = doc["data_type"];
  Serial.println(" " + dst);
  Serial.println(" " + dataType);
  if (dataType == "info") {
    String response = "OK";
    lora.send((byte*)response.c_str(), response.length(), 0x0001, 0x0001);
  }
}

void MyMessageHandler::onData(JsonDocument &doc) {

}

void MyMessageHandler::onReject(JsonDocument &doc) {

}

void MyMessageHandler::onAccept(JsonDocument &doc) {

}

void MyMessageHandler::onPropose(JsonDocument &doc) {

}

void MyMessageHandler::onAnnouncement(JsonDocument &doc) {

}

void MyMessageHandler::onCancel(JsonDocument &doc) {
  
}

void MyMessageHandler::tick() {

}
