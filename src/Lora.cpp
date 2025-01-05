#include <ArduinoJson.h>
#include "Lora.h"
#include "MessageHandler.h"

#define _DEBUG

void Lora::init(uint16_t pan_id, uint16_t own_id, int8_t rst_pin) {
  Serial.println("Start init Lora");

  m_pan_id = pan_id;
  m_own_id = own_id;
  m_rst_pin = rst_pin;
  pinMode(m_rst_pin, OUTPUT);
  digitalWrite(5, HIGH);

  Serial2.begin(115200);
  while (!Serial2);
  //  起動に約5msかかる
  delay(10);

  if (!wait("\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  if (!wait("Select Mode [1.terminal or 2.processor]\r\n", 100)) {
    digitalWrite(m_rst_pin, LOW);
    //  1ms 以上のLOWが必要
    delay(5);
    digitalWrite(m_rst_pin, HIGH);
    delay(10);
    if (!wait("\r\n", 100)) {
      Serial.println("Unexpected response from Lora");
      return;
    }
    if (!wait("Select Mode [1.terminal or 2.processor]\r\n", 100)) {
      Serial.println("Unexpected response from Lora");
      return;
    }
  }

  Serial2.write("processor\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("protocol 1\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("bw 6\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("sf 7\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("channel 1\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  char own_id_buf[4];
  sprintf(own_id_buf, "%04X", m_own_id);
  Serial2.write("ownid ");
  Serial2.write(own_id_buf);
  Serial2.write("\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  char pan_id_buf[4];
  sprintf(pan_id_buf, "%04X", m_pan_id);
  Serial2.write("panid ");
  Serial2.write(pan_id_buf);
  Serial2.write("\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("format 2\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("transmode 2\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  // Serial2.write("ack 1\r\n");
  Serial2.write("ack 2\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("rcvid 1\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("rssi 1\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("power -4\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("save\r\n");
  if (!wait("OK\r\n", 1000)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial2.write("start\r\n");
  if (!wait("OK\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  if (!wait("\r\n", 100)) {
    Serial.println("Unexpected response from Lora");
    return;
  }

  Serial.println("End init Lora");
}

void Lora::send(byte *data, size_t length, uint16_t pan_id, uint16_t dst_id) {
  size_t index = 0;
  byte frame[1+8+50];
  char pan_id_buf[4];
  sprintf(pan_id_buf, "%04X", pan_id);
  memcpy(frame+1, pan_id_buf, 4);
  char dst_id_buf[4];
  sprintf(dst_id_buf, "%04X", dst_id);
  memcpy(frame+5, dst_id_buf, 4);

  while (index < length) {
    int8_t data_length = index + 49 < length ? 49 : length - index;
    int8_t frame_length = 9 + data_length;
    frame[0] = (byte)(frame_length & 0xff);
    frame[9] = index + data_length == length ? '1' : '0';
    memcpy(frame+10, data+index, data_length);
    //  Send
    Serial.write(frame, frame_length+1);
    Serial.print("\r\n");
    index += 49;
  }
}

String Lora::read() {
  String buffer;
  while (1) {
    while (Serial2.available() > 0) {
      buffer += (char) Serial2.read();
    }
  }
  #ifdef _DEBUG
    Serial.print("Received: (");
    Serial.print(buffer.length());
    Serial.print(") ");
    Serial.println(buffer);
  #endif
  return buffer;
}

bool Lora::wait(String str, unsigned long max_delay) {
  #ifdef _DEBUG
    Serial.print("Waiting: (");
    Serial.print(str.length());
    Serial.println(") " + str);
  #endif
  unsigned long start = millis();
  unsigned long now = millis();
  String buffer;
  while (true) {
    now = millis();
    if (now - start >= max_delay) {
      break;
    }
    while (Serial2.available() > 0) {
      buffer += (char) Serial2.read();
      if (str == buffer) {
        #ifdef _DEBUG
          Serial.print("Received expected: (");
          Serial.print(buffer.length());
          Serial.println(") " + buffer);
        #endif
        return true;
      };
    }
  }
  #ifdef _DEBUG
    Serial.print(max_delay);
    Serial.print(now - start);
    Serial.print("Received unexpected: (");
    Serial.print(buffer.length());
    Serial.println(") " + buffer);
  #endif
  return false;
}

void Lora::receive() {
  while (Serial2.available()) {
    byte c = Serial2.read();
    int length = int(c);
    byte* buffer;
    buffer = new byte[length];
    for (int i = 0; i < length; i++) {
      buffer[i] = Serial2.read();
    }
    byte rssi[4];
    memcpy(rssi, buffer, 4);
    byte pan_id[4];
    memcpy(pan_id, buffer+4, 4);
    byte snd_id[4];
    memcpy(snd_id, buffer+8, 4);
    byte* payload;
    payload = new byte[length - 13];
    memcpy(payload, buffer+13, length - 13);
    String key = String(pan_id, 4) + String(snd_id, 4);
    m_buf[key] += String(payload, length-13);
    if (buffer[12] == '1') {
      handleMessage(m_buf[key]);
      m_buf[key] = "";
    }
  }
}

void Lora::handleMessage(String message) {
  JsonDocument doc;
  deserializeJson(doc, message);

  int type = doc["type"];
  Serial.println("Received: " + type);
  switch(static_cast<MessageType>(type)) {
    case MessageType::REQUEST:
      for (int i=0; i < this->m_handlers_.size(); i++) {
        this->m_handlers_[i]->onRequest(doc);
      }
      break;
  }
}

void Lora::addHandler(MessageHandler &handler) {
  m_handlers_.push_back(&handler);
}
