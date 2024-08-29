
#pragma once
#include "url.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
namespace sh {

class HttpGetRequest {
public:
  HttpGetRequest(const std::string &url) : url(url) {}

  bool sendRequest();

private:
  std::string url;
};

} 
