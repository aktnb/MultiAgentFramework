#include "MessageHandler.h"

void serializeMessage(Request &message, String &json) {
  JsonDocument doc;
  doc["type"] = "request";
  doc["id"] = message.id;
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["data_type"] = message.dataType;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Request &message) {
  message.id = doc["id"].as<String>();
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.dataType = doc["data_type"].as<String>();;
}
void serializeMessage(Data &message, String &json) {
  JsonDocument doc;
  doc["type"] = "data";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["data_type"] = message.dataType;
  doc["data"] = message.data;
  doc["contract_id"] = message.contractId;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Data &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.dataType = doc["data_type"].as<String>();;
  message.data = doc["data"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
}
void serializeMessage(Reject &message, String &json) {
  JsonDocument doc;
  doc["type"] = "reject";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["contract_id"] = message.contractId;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Reject &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
}
void serializeMessage(Accept &message, String &json) {
  JsonDocument doc;
  doc["type"] = "accept";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["contract_id"] = message.contractId;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Accept &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
}
void serializeMessage(Announce &message, String &json) {
  JsonDocument doc;
  doc["type"] = "announce";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["contract_id"] = message.contractId;
  doc["data_type"] = message.dataType;
  doc["frequency"] = message.frequency;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Announce &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
  message.dataType = doc["data_type"].as<String>();;
  message.frequency = doc["frequency"].as<int>();
}
void serializeMessage(Propose &message, String &json) {
  JsonDocument doc;
  doc["type"] = "propose";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["contract_id"] = message.contractId;
  doc["data_type"] = message.dataType;
  doc["frequency"] = message.frequency;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Propose &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
  message.dataType = doc["data_type"].as<String>();;
  message.frequency = doc["frequency"].as<int>();
}
void serializeMessage(Cancel &message, String &json) {
  JsonDocument doc;
  doc["type"] = "cancel";
  doc["dst"] = message.dst;
  doc["src"] = message.src;
  doc["contract_id"] = message.contractId;
  serializeJson(doc, json);
}
void deserializeMessage(JsonDocument &doc, Cancel &message) {
  message.dst = doc["dst"].as<String>();
  message.src = doc["src"].as<String>();
  message.contractId = doc["contract_id"].as<String>();
}
