
/********************************************/
//
//              CopyRight Moatasem elsayed
//
/********************************************/
/*
author : Moatasem Elsayed
date :Fri May 17 11:10:26 AM EEST 2024
brief:
*/
#include "parser.hpp"
#include <iostream>
#include <vector>

namespace sh {
parser::parser() {}
parser::~parser() {}
void parser::log(std::vector<devices> dev) {
  for (auto &element : dev) {
    std::cout << "Device ID: " << element._id << std::endl;
    std::cout << "Device Identifier: " << element.identifier << std::endl;
    std::cout << "Device Name: " << element.name << std::endl;
    std::cout << "Device Status: " << element.status << std::endl;
    std::cout << "Device __v: " << element.__v << std::endl;
  }
}

std::vector<devices> parser::parse(std::string msg) {
  std::vector<devices> output;
  if (msg.empty()) {
    return output;
  }
  std::vector<std::string> dev =
      convertToVector(msg); //"vector{<e1>,<e2>,<e3>}"
  for (auto &element : dev) {
    devices device = parse_device(element);
    output.push_back(device);
  }
  log(output);
  return output;
}

std::vector<std::string> parser::convertToVector(std::string msg) {
  msg.insert(0, "{ \"data\":");
  msg.append("}");
  std::cout << msg << std::endl;
  // nlohmann::json j = nlohmann::json::parse(msg);
  // Parse the JSON string
  nlohmann::json jsonData = nlohmann::json::parse(
      msg); //{data:[{id:1,name:led,status:off},{id:2,name:led,status:on},{id:3,name:led,status:off}]
  std::vector<std::string> dev;
  for (
      auto &element : jsonData
          ["data"]) { //[{id:1,name:led,status:off},{id:2,name:led,status:on},{id:3,name:led,status:off}]
    dev.push_back(element.dump());
  }
  //{id:1,name:led,status:off}
  //{id:2,name:led,status:on}
  //{id:3,name:led,status:off}
  //
  return dev;
}

devices parser::parse_device(std::string msg) {
  devices device;
  nlohmann::json j = nlohmann::json::parse(msg);
  device._id = j["_id"];
  device.identifier = j["identifier"];
  device.name = j["name"];
  device.status = j["status"];
  return device;
}
} // namespace sh
