
#pragma once
#include "idevice.hpp"
namespace sh {
class AirConditioner : public Idevice {

public:
  AirConditioner();
  ~AirConditioner();
  bool run(devices status);

private:
};
} 
