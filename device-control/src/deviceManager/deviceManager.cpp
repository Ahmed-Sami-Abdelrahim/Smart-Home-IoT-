#include "deviceManager.hpp"

namespace sh {

deviceManager::deviceManager() {}

deviceManager::~deviceManager() {}

// Method to manage devices based on their statuses
bool deviceManager::manage(std::vector<devices> status_dev) {
  // Iterate over each device in the manager
  for (auto &device : m_devices) {
    // Iterate over each device status from the provided list
    for (auto &sd : status_dev) { 
      // Check if the current device matches the status device by name
      if (device->contains(sd.name)) {
        // Run the device with the provided status
        device->run(sd);
      }
    }
  }
  return true;
}

// Method to add a device to the manager
void deviceManager::add_device(std::shared_ptr<Idevice> ptr_device) {
  // Add the provided device to the list of managed devices
  m_devices.push_back(ptr_device);
}
}
