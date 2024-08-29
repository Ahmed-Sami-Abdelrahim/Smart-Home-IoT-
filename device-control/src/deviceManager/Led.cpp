#include "Led.hpp"
#include "unistd.h"  // Provides access to the POSIX operating system API
#include <algorithm>
#include <fcntl.h>   // Provides file control options
#include <iostream>  // Provides input/output stream operations

namespace sh {

// Constructor for Led
Led::Led() {
  // Initialize the list of possible names for this device
  possible_names.assign({
      "led",
      "lamp",
  });
}

// Destructor for Led
Led::~Led() {}

// Method to run the LED with the given status
bool Led::run(devices status) {
  std::cout << "LED is running now " << status.name << " status "
            << status.status << std::endl;

#if 1
  // Check if the status has changed
  if (last_status != status.status) {
    last_status = status.status; // Update last_status

    // Open the LED device file in write-only mode
    int fd = open("/dev/led-home", O_WRONLY);
    if (fd < 0) {
      std::cerr << "Error opening LED device file" << std::endl;
      return false; // Return false if file cannot be opened
    }

    // Write the new status to the device
    if (status.status) {
      // Write "1" to turn the LED on
      int ret = write(fd, "1", 1);
      if (ret < 0) {
        std::cerr << "Error writing to LED device file" << std::endl;
        close(fd);
        return false; // Return false if write fails
      }
    } else {
      // Write "0" to turn the LED off
      int ret = write(fd, "0", 1);
      if (ret < 0) {
        std::cerr << "Error writing to LED device file" << std::endl;
        close(fd);
        return false; // Return false if write fails
      }
    }

    // Close the device file
    close(fd);
  }
#endif

  return true; 
}
}
