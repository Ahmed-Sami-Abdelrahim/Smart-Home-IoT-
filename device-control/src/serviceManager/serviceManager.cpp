#include "serviceManager.hpp"
#include "AirConditioner.hpp"
#include "Led.hpp"
#include <memory>

namespace sh {

// Constructor for serviceManager
serviceManager::serviceManager() {
  // Initialize the client handler
  m_clientHandler.init();
  
  // Add devices to the device manager
  // Creates shared pointers for Led and AirConditioner and adds them to the manager
  m_deviceManager.add_device(std::make_shared<Led>());
  m_deviceManager.add_device(std::make_shared<AirConditioner>());
}

serviceManager::~serviceManager() {

}

// Main run method for serviceManager
bool serviceManager::run() {
  // Handle client request and get a response pair consisting of result and response data
  std::pair<Result, std::string> response = m_clientHandler.requestHandle();
  
  // Check if the request was successful (Result::FAILED is not the result)
  if (response.first != Result::FAILED) {
    // Parse the response data into a vector of devices
    std::vector<devices> dev = m_parser.parse(response.second);
    
    // Manage the devices by passing the parsed data to the device manager
    m_deviceManager.manage(dev);
  }

  return true; 
}
}
