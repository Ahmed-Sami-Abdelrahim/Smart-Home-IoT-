
#pragma once
#include "idevice.hpp"
#include <memory>
#include <vector>

namespace sh {
class deviceManager {

public:
  deviceManager();
  ~deviceManager();
  bool manage(std::vector<devices> dev);
  void add_device(std::shared_ptr<Idevice> ptr_device);

private:
  std::vector<std::shared_ptr<Idevice>> m_devices;
};
} 
