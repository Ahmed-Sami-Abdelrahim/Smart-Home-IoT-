#include "AirConditioner.hpp"
#include "HttpGetClient.hpp"
#include "url.hpp"
#include <iostream>

namespace sh {

AirConditioner::AirConditioner() {
  // Initialize possible names for the air conditioner
  possible_names.assign({
      "AC",
      "ac",
      "airconditioner",
  });
}

// Destructor for AirConditioner
AirConditioner::~AirConditioner() {}

// Method to run the air conditioner with a given status
bool AirConditioner::run(devices status) {
  // Print the status of the air conditioner
  std::cout << "airconditioner is running now " << status.name << "status "
            << status.status << std::endl;

  // Check if the status has changed since the last update
  if (last_status != status.status) {
    last_status = status.status; // Update the last status
    std::string url;

    // Determine the URL to use based on the new status
    if (last_status) { // If status is 'true' (assuming 'true' means 'on')
      url = AC_URL_ON; // URL to turn the AC on
      std::cout << "AC is on" << std::endl;
    } else { // If status is 'false' (assuming 'false' means 'off')
      url = AC_URL_OFF; // URL to turn the AC off
    }

    // Create an HTTP GET request object with the determined URL
    sh::HttpGetRequest request(url);

    // Send the HTTP GET request
    if (request.sendRequest()) {
      std::cout << "Request sent successfully" << std::endl;
    } else {
      std::cerr << "Failed to send request" << std::endl;
    }
  }

  // Return true to indicate the function completed successfully
  return true;
}
}
