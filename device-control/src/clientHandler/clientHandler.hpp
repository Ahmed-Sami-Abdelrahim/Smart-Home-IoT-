
#pragma once
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
namespace sh {
enum class Result : uint8_t {
  SUCCESS,
  FAILED,

};
class clientHandler {

public:
  clientHandler();
  ~clientHandler();
  Result init();
  std::pair<Result, std::string> requestHandle();

private:
  int m_serverSocket;
};
} 