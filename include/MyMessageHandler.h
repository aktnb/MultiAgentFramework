#ifndef _MyMessageHandler_h
#define _MyMessageHandler_h

#include "MessageHandler.h"
#include "Lora.h"
#include <ArduinoJson.h>

class MyMessageHandler : public MessageHandler {
  Lora lora;
public:
  void init(Lora &lora);
  void onRequest(JsonDocument &doc);
  void onData(JsonDocument &doc);
  void onReject(JsonDocument &doc);
  void onAccept(JsonDocument &doc);
  void onPropose(JsonDocument &doc);
  void onAnnouncement(JsonDocument &doc);
  void onCancel(JsonDocument &doc);

  void tick();
};

#endif
