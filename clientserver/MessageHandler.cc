#include "MessageHandler.h"
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include <cstdlib>
#include <string>

MessageHandler::MessageHandler(const Connection& c) : conn(c) {}

void MessageHandler::send_byte(unsigned char& code) {
  conn.write(code);
}

void MessageHandler::send_code(int& code) {
  send_int(code);
}

void MessageHandler::send_int(int& value) {
  conn.write((value >> 24) & 0xFF);
  conn.write((value >> 16) & 0xFF);
  conn.write((value >> 8)  & 0xFF);
  conn.write(value & 0xFF);
}

void MessageHandler::send_int_parameter(int& param) {
  send_code(Protocol::PAR_NUM);
  send_int(param);
}

void MessageHandler::send_string_parameter(string& param) {
  send_code(Protocol::PAR_STRING);
  send_int(param.length())
  for (int i = 0; i < param.length(); ++i {
    sendByte(param[i]);
  }
}

unsigned char MessageHandler::recv_byte() {
  return conn.read();
}

int MessageHandler::recv_code() {
  return recv_int();
}

int MessageHandler::recv_int() {
  unsigned char byte1 = recv_byte();
  unsigned char byte2 = recv_byte();
  unsigned char byte3 = recv_byte();
  unsigned char byte4 = recv_byte();
  return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int MessageHandler::recv_int_parameter() {
  int code = recv_code();
  if (code != Protocol.PAR_NUM) {
    throw new ConnectionClosedException();
  }
  return recv_int();
}

std::string MessageHandler::recv_string_paramter() {
  int code = recv_code();
  if (code != Protocol::PAR_STRING) {
    throw new ConnectionClosedException();
  }
  int n = recv_int();
  if (n < 0) {
    throw new ConnectionClosedException();
  }
  std::string result;
  for (int i = 1; i <= n; ++i) {
    unsigned char ch = conn.read();
    result += ch;
  }
  return result;
}
