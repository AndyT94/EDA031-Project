#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>
#include <memory>

class MessageHandler {
public:
  void send_code(const std::shared_ptr<Connection>& conn, int code);
  void send_int(const std::shared_ptr<Connection>& conn, int value);
  void send_int_parameter(const std::shared_ptr<Connection>& conn, int param);
  void send_string_parameter(const std::shared_ptr<Connection>& conn, const std::string& param);
  int recv_code(const std::shared_ptr<Connection>& conn);
  int recv_int(const std::shared_ptr<Connection>& conn);
  int recv_int_parameter(const std::shared_ptr<Connection>& conn);
  std::string recv_string_paramter(const std::shared_ptr<Connection>& conn);
private:
  void send_byte(const std::shared_ptr<Connection>& conn, int code);
  unsigned char recv_byte(const std::shared_ptr<Connection>& conn);
};

#endif
