#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>

class MessageHandler {
public:
  MessageHandler(const Connection& c);
  void send_code(int& code);
  void send_int(int& value);
  void send_int_parameter(int& param);
  void send_string_parameter(std::string& param);
  int recv_code();
  int recv_int();
  int recv_int_parameter();
  std::string recv_string_paramter();
private:
  Connection conn;
  void send_byte(int& code);
  unsigned char recv_byte();
};

#endif
