#ifndef _MyMessageHandler_h
#define _MyMessageHandler_h

#include "MessageHandler.h"
#include "Lora.h"
#include <ArduinoJson.h>

class MyMessageHandler : public MessageHandler {
  Lora lora;
public:
  void init(Lora &lora);
  void onRequest(Request &request);
  void onData(Data &data);
  void onReject(JsonDocument &doc);
  void onAccept(JsonDocument &doc);
  void onPropose(JsonDocument &doc);
  void onAnnouncement(JsonDocument &doc);
  void onCancel(JsonDocument &doc);

  void tick();
};

#endif
