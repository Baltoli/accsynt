#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace idlr {

class call {
public:
  explicit call(std::string, std::vector<std::string>);

private:
  std::string target_;
  std::vector<std::string> args_;
};

class spec {
public:
  explicit spec(std::string, std::unordered_map<std::string, call>);

private:
  std::string func_;
  std::unordered_map<std::string, call> replacements_;
};

} // namespace idlr
