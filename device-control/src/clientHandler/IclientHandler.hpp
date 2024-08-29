
#pragma once
namespace sh {
class IclientHandler {

public:
  virtual ~IclientHandler();
  void init();
  void connect();
};
} 
