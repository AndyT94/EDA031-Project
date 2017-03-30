#include "MessageHandler.h"
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocolviolationexception.h"
#include <cstdlib>
#include <string>
#include <memory>

using namespace std;

void MessageHandler::send_byte(const shared_ptr<Connection>& conn, int code) {
  try {
    conn->write(static_cast<unsigned char>(code));
  } catch (...) {
    throw ConnectionClosedException();
  }
}

void MessageHandler::send_code(const shared_ptr<Connection>& conn, int code) {
  send_byte(conn, code);
}

void MessageHandler::send_int(const shared_ptr<Connection>& conn, int value) {
  send_byte(conn, (value >> 24) & 0xFF);
  send_byte(conn, (value >> 16) & 0xFF);
  send_byte(conn, (value >> 8)  & 0xFF);
  send_byte(conn, value & 0xFF);
}

void MessageHandler::send_int_parameter(const shared_ptr<Connection>& conn, int param) {
  send_code(conn, Protocol::PAR_NUM);
  send_int(conn, param);
}

void MessageHandler::send_string_parameter(const shared_ptr<Connection>& conn, const string& param) {
  send_code(conn, Protocol::PAR_STRING);
  send_int(conn, param.length());
  for (unsigned int i = 0; i < param.length(); ++i) {
    send_byte(conn, param[i]);
  }
}

unsigned char MessageHandler::recv_byte(const shared_ptr<Connection>& conn) {
  int byte;
  try {
    byte = conn->read();
  } catch(...) {
    throw ConnectionClosedException();
  }
  return byte;
}

int MessageHandler::recv_code(const shared_ptr<Connection>& conn) {
  return recv_byte(conn);
}

int MessageHandler::recv_int(const shared_ptr<Connection>& conn) {
  unsigned char byte1 = recv_byte(conn);
  unsigned char byte2 = recv_byte(conn);
  unsigned char byte3 = recv_byte(conn);
  unsigned char byte4 = recv_byte(conn);
  return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int MessageHandler::recv_int_parameter(const shared_ptr<Connection>& conn) {
  int code = recv_code(conn);
  if (code != Protocol::PAR_NUM) {
    throw ProtocolViolationException("Receive numeric parameter",
        Protocol::PAR_NUM, code);
  }
  return recv_int(conn);
}

std::string MessageHandler::recv_string_paramter(const shared_ptr<Connection>& conn) {
  int code = recv_code(conn);
  if (code != Protocol::PAR_STRING) {
    throw ProtocolViolationException("Receive string parameter",
        Protocol::PAR_STRING, code);
  }
  int n = recv_int(conn);
  if (n < 0) {
    throw ProtocolViolationException("Receive string parameter",
        "Number of characters < 0");
  }
  std::string result = "";
  for (int i = 1; i <= n; ++i) {
    char ch = conn->read();
    result += ch;
  }
  return result;
}
