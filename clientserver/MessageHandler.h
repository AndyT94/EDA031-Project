#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>

class MessageHandler {
public:
  void send_code(const Connection& conn, int code);
  void send_int(const Connection& conn, int value);
  void send_int_parameter(const Connection& conn, int param);
  void send_string_parameter(const Connection& conn, std::string& param);
  int recv_code(const Connection& conn);
  int recv_int(const Connection& conn);
  int recv_int_parameter(const Connection& conn);
  std::string recv_string_paramter(const Connection& conn);
private:
  void send_byte(const Connection& conn, int code);
  unsigned char recv_byte(const Connection& conn);
};

#endif
