#ifndef _MessageHandler_h
#define _MessageHandler_h
#include <ArduinoJson.h>

enum struct MessageType {
  REQUEST = 0,
  DATA = 1,
  REJECT = 2,
  ACCEPT = 3,
  PROPOSE = 4,
  ANNOUNCEMENT = 5,
  CANCEL = 6,
};

class MessageHandler {
public:
  virtual void onRequest(JsonDocument &doc) = 0;
  virtual void onData(JsonDocument &doc) = 0;
  virtual void onReject(JsonDocument &doc) = 0;
  virtual void onAccept(JsonDocument &doc) = 0;
  virtual void onPropose(JsonDocument &doc) = 0;
  virtual void onAnnouncement(JsonDocument &doc) = 0;
  virtual void onCancel(JsonDocument &doc) = 0;
};

#endif
