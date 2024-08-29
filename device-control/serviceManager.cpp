#include "serviceManager.hpp"
#include <vector>

namespace sh {

serviceManager::serviceManager() { 
  // Initialize the client handler when the serviceManager is created
  m_clientHandler.init(); 
}

serviceManager::~serviceManager() {}

bool serviceManager::run() {
  // Handle a client request and get a response
  std::pair<Result, std::string> response = m_clientHandler.requestHandle();
  
  // Check if the request handling failed
  if (response.first == Result::FAILED) {
    return false; // Indicate failure
  }
  
  // Parse the response into a vector of devices
  std::vector<devices> dev = m_parser.parse(response.second);
  
  // Manage the devices
  m_deviceManager.manage(dev);
 
  return true;
}

} 
