#include "Lora.h"

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

  Serial.println("End init Lora");
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
