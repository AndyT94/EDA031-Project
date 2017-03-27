#include "MessageHandler.h"
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include <cstdlib>
#include <string>

MessageHandler::MessageHandler(const Connection& c) : conn(c) {}

void MessageHandler::send_byte(int& code) {
  try {
    conn.write(static_cast<unsigned char>(code));
  } catch (...) {
    throw ConnectionClosedException();
  }
}

void MessageHandler::send_code(int& code) {
  send_byte(code);
}

void MessageHandler::send_int(int& value) {
  send_byte((value >> 24) & 0xFF);
  send_byte((value >> 16) & 0xFF);
  send_byte((value >> 8)  & 0xFF);
  send_byte(value & 0xFF);
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
  int byte;
  try {
    byte = conn.read();
  } catch(...) {
    throw ConnectionClosedException();
  }
  return byte;
}

int MessageHandler::recv_code() {
  return recv_byte();
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
    throw ProtocolViolationException("Receive numeric parameter",
        Protocol.PAR_NUM, code);
  }
  return recv_int();
}

std::string MessageHandler::recv_string_paramter() {
  int code = recv_code();
  if (code != Protocol::PAR_STRING) {
    throw ProtocolViolationException("Receive string parameter",
        Protocol.PAR_STRING, code);
  }
  int n = recv_int();
  if (n < 0) {
    throw ProtocolViolationException("Receive string parameter",
        "Number of characters < 0");
  }
  std::string result = "";
  for (int i = 1; i <= n; ++i) {
    char ch = conn.read();
    result += ch;
  }
  return result;
}
