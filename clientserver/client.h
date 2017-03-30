#ifndef CLIENT_H
#define CLIENT_H

#include "connection.h"
#include "server.h"
#include <string>

class Client{
public:
  void writeNumber(const Connection& conn, int value);

  string readString(const Connection& conn);

private:

}

#endif
