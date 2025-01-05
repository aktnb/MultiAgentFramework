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

struct Request {
  String id;
  String dst;
  String src;
  String dataType;
};

struct Data {
  String dst;
  String src;
  String dataType;
  String data;
  String contractId;
};

struct Reject {
  String dst;
  String src;
  String contractId;
};

struct Accept {
  String dst;
  String src;
  String contractId;
};

struct Propose {
  String dst;
  String src;
  String contractId;
  String dataType;
  int frequency;
};

struct Announce {
  String dst;
  String src;
  String contractId;
  String dataType;
  int frequency;
};

struct Cancel {
  String dst;
  String src;
  String contractId;
};

void serializeMessage(Request &message, String &json);
void serializeMessage(Data &message, String &json);
void serializeMessage(Reject &message, String &json);
void serializeMessage(Accept &message, String &json);
void serializeMessage(Announce &message, String &json);
void serializeMessage(Propose &message, String &json);
void serializeMessage(Cancel &message, String &json);

void deserializeMessage(JsonDocument &doc, Request &message);
void deserializeMessage(JsonDocument &doc, Data &message);
void deserializeMessage(JsonDocument &doc, Reject &message);
void deserializeMessage(JsonDocument &doc, Accept &message);
void deserializeMessage(JsonDocument &doc, Announce &message);
void deserializeMessage(JsonDocument &doc, Propose &message);
void deserializeMessage(JsonDocument &doc, Cancel &message);


class MessageHandler {
public:
  virtual void onRequest(Request &request) = 0;
  virtual void onData(JsonDocument &doc) = 0;
  virtual void onReject(JsonDocument &doc) = 0;
  virtual void onAccept(JsonDocument &doc) = 0;
  virtual void onPropose(JsonDocument &doc) = 0;
  virtual void onAnnouncement(JsonDocument &doc) = 0;
  virtual void onCancel(JsonDocument &doc) = 0;
};

#endif
