#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>
#include <memory>

class MessageHandler {
public:
  void send_code(std::shared_ptr<Connection>& conn, int code);
  void send_int(std::shared_ptr<Connection>& conn, int value);
  void send_int_parameter(std::shared_ptr<Connection>& conn, int param);
  void send_string_parameter(std::shared_ptr<Connection>& conn, const std::string& param);
  int recv_code(std::shared_ptr<Connection>& conn);
  int recv_int(std::shared_ptr<Connection>& conn);
  int recv_int_parameter(std::shared_ptr<Connection>& conn);
  std::string recv_string_paramter(std::shared_ptr<Connection>& conn);
private:
  void send_byte(std::shared_ptr<Connection>& conn, int code);
  unsigned char recv_byte(std::shared_ptr<Connection>& conn);
};

#endif
