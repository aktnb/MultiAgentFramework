#ifndef _Lora_h
#define _Lora_h
#include <Arduino.h>
#include <map>
#include <vector>
#include "MessageHandler.h"

class Lora {
  uint16_t m_pan_id;
  uint16_t m_own_id;
  int8_t m_rst_pin;
  std::map<String, String> m_buf;
  std::vector<MessageHandler*> m_handlers_;
  String read();
  bool wait(String str, unsigned long max_delay);
  void handleMessage(String str);
public:
  void init(uint16_t pan_id, uint16_t own_id, int8_t rst_pin);
  void send(byte *data, size_t length, uint16_t pan_id, uint16_t dst_id);
  void receive();
  void addHandler(MessageHandler &handler);
};

#endif
