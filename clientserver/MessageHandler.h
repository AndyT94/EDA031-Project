#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>
#include <memory>

class MessageHandler {
public:
  void send_code(Connection& conn, int code);
  void send_int(Connection& conn, int value);
  void send_int_parameter(Connection& conn, int param);
  void send_string_parameter(Connection& conn, const std::string& param);
  int recv_code(Connection& conn);
  int recv_int(Connection& conn);
  int recv_int_parameter(Connection& conn);
  std::string recv_string_paramter(Connection& conn);
private:
  void send_byte(Connection& conn, int code);
  unsigned char recv_byte(Connection& conn);
};

#endif
