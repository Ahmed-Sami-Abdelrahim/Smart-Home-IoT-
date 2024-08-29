#include "HttpGetClient.hpp"
#include "serviceManager.hpp"
#include "url.hpp"
int main() {
  sh::serviceManager serviceManager;

  bool continueRunning = true;
  while (continueRunning) {
    continueRunning = serviceManager.run();
  }

  return 0;
}