#pragma once

#include <memory>

namespace llvm {
  class Module;
}

#define LOAD_MODULE(name, str) \
  auto name = load_module(str); \
  REQUIRE(mod);

std::unique_ptr<llvm::Module> load_module(const std::string& str);
