
#pragma once
#include "idevice.hpp"
#include <vector>
namespace sh {
class Led : public Idevice {

public:
  Led();
  ~Led();
  bool run(devices status);

private:
};
} 
