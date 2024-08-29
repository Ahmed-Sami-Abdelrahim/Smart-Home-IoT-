#include "HttpGetClient.hpp"
#include <iostream>

namespace sh {

// Method to send an HTTP GET request
bool HttpGetRequest::sendRequest() {
  // Extract the host part of the URL by removing the API path
  std::string host = url.substr(0, url.find("/api"));
  host.erase(0, host.find("://") + 3); // Remove "http://" or "https://"
  std::cout << "Host: " << host << std::endl;

  // Resolve the host to an IP address
  struct hostent *server = gethostbyname(host.c_str());
  std::string path = url.substr(url.find("/api")); // Extract the path from the URL

  // Check if the host was resolved successfully
  if (server == nullptr) {
    std::cerr << "Error: No such host" << std::endl;
    return false;
  }

  // Create a socket for communication
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error opening socket" << std::endl;
    return false;
  }

  // Set up the server address structure
  struct sockaddr_in serv_addr;
  std::memset(&serv_addr, 0, sizeof(serv_addr)); // Clear the structure
  serv_addr.sin_family = AF_INET; // Set address family to AF_INET (IPv4)
  std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length); // Copy resolved IP address
  serv_addr.sin_port = htons(80); // Set port number to 80 (HTTP)

  // Connect to the server
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Error connecting" << std::endl;
    close(sockfd); // Close the socket on error
    return false;
  }

  // Formulate the HTTP GET request
  std::string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host +
                        "\r\n" + "Connection: close\r\n\r\n";

  // Send the request to the server
  if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
    std::cerr << "Error writing to socket" << std::endl;
    close(sockfd); // Close the socket on error
    return false;
  }

  // Read and display the server response
  char buffer[4096];
  std::memset(buffer, 0, sizeof(buffer)); // Clear the buffer
  while (read(sockfd, buffer, sizeof(buffer) - 1) > 0) {
    std::cout << buffer; // Output the response
    std::memset(buffer, 0, sizeof(buffer)); // Clear the buffer for the next read
  }

  // Close the socket after communication is complete
  close(sockfd);
  return true; // Indicate successful completion
}
}
