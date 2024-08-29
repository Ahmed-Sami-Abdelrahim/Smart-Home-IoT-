
#pragma once
#include "clientHandler.hpp"
#include "deviceManager.hpp"
#include "parser.hpp"
#include <bits/stdc++.h>
#include <memory>
namespace sh {
class serviceManager {

public:
  serviceManager();
  ~serviceManager();
  bool run();

private:
  clientHandler m_clientHandler;
  parser m_parser;
  deviceManager m_deviceManager;
};
} 
