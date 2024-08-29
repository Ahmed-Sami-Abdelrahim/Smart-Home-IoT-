
#pragma once
/********************************************/
//
//              CopyRight Moatasem elsayed
//
/********************************************/
/*
author : Moatasem elsayed
date :Fri May 17 11:10:25 AM EEST 2024
brief:
*/
#include "idevice.hpp"
#include "nlohmann/json.hpp"
#include <vector>
namespace sh {

class parser {

public:
  parser();
  ~parser();
  //
  std::vector<devices> parse(std::string msg);

  void log(std::vector<devices> dev);

private:
  std::vector<std::string> convertToVector(std::string msg);
  devices parse_device(std::string msg);
};
} // namespace sh
