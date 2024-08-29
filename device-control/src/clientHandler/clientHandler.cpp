
#include "clientHandler.hpp"
#include <cstdint>
#include <utility>

namespace sh {
clientHandler::clientHandler() {}
clientHandler::~clientHandler() { close(m_serverSocket); }

Result clientHandler::init() {
  m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (m_serverSocket == -1) {
    std::cerr << "Failed to create socket." << std::endl;
    return Result::FAILED;
  }

  // Bind the socket to a specific IP address and port
  struct sockaddr_in serverAddress {};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(2222);

  if (bind(m_serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) == -1) {
    std::cerr << "Failed to bind socket." << std::endl;
    close(m_serverSocket);
    return Result::FAILED;
  }

  // Listen for incoming connections
  if (listen(m_serverSocket, 5) == -1) {
    std::cerr << "Failed to listen on socket." << std::endl;
    close(m_serverSocket);
    return Result::FAILED;
  }
  std::cout << "Server listening on port 2222..." << std::endl;

  return Result::SUCCESS;
}

std::pair<Result, std::string> clientHandler::requestHandle() {
  // Accept incoming connections
  struct sockaddr_in clientAddress {};
  socklen_t clientAddressLength = sizeof(clientAddress);
  int clientSocket = accept(m_serverSocket, (struct sockaddr *)&clientAddress,
                            &clientAddressLength);
  if (clientSocket == -1) {
    std::cerr << "Failed to accept connection." << std::endl;
    close(clientSocket);
    close(m_serverSocket);
    return std::make_pair(Result::FAILED, "");
  }
  // Receive the GET request
  char buffer[4000];
  memset(buffer, 0, sizeof(buffer));
  ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  if (bytesRead == -1) {
    std::cerr << "Failed to receive data." << std::endl;
    close(clientSocket);
    close(m_serverSocket);
    return std::make_pair(Result::FAILED, "");
  }
  // Send the response to the client
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 7\r\n\r\nSuccess";
  ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
  if (bytesSent == -1) {
    std::cerr << "Failed to send response." << std::endl;
    close(clientSocket);
    close(m_serverSocket);
    return std::make_pair(Result::FAILED, "");
  }
  std::string buffer_str(buffer);
  // Print the received request
  std::cout << "Received GET request: " << buffer_str << std::endl;
  // http response

  auto body_position = buffer_str.find("\r\n\r\n");
  if (body_position == std::string::npos) {
    std::cerr << "Failed to find body position." << std::endl;
    close(clientSocket);
    // close(m_serverSocket);
    return std::make_pair(Result::FAILED, "");
  }
  std::cout << body_position << std::endl;
  buffer_str = buffer_str.substr(body_position + 4);
  // Close the sockets
  close(clientSocket);
  return std::make_pair(Result::SUCCESS, buffer_str);
}
} 
