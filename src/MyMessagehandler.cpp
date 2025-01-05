#include <Arduino.h>
#include <ArduinoJson.h>
#include "MyMessageHandler.h"
#include "Lora.h"


void MyMessageHandler::init(Lora &lora) {
  this->lora = lora;
}

void MyMessageHandler::onRequest(Request &request) {
  Serial.println("Request received");
  Serial.println(" dst: " + request.dst);
  Serial.println(" src: " + request.src);
  Serial.println(" data type: " + request.dataType);

  if (request.dataType == "info") {
    Data data;
    int panId;
    sscanf(request.src.substring(0, 4).c_str(), "%x", &panId);
    int srcId;
    sscanf(request.src.substring(4, 8).c_str(), "%x", &srcId);
    data.src = request.dst;
    data.dst = request.src;
    data.dataType = "info";
    data.data = "temperature,10";
    data.contractId = "";
    String str;
    serializeMessage(data, str);
    lora.send((byte*)str.c_str(), str.length(), panId, srcId);
  }
}

void MyMessageHandler::onData(Data &data) {
  Serial.println("Data received");
  Serial.println(" dst: " + data.dst);
  Serial.println(" src: " + data.src);
  Serial.println(" data type: " + data.dataType);
  Serial.println(" data: " + data.data);
  Serial.println(" contract id: " + data.contractId);
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
