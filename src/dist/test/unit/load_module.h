#pragma once

#include <memory>

namespace llvm {
  class Module;
}

std::unique_ptr<llvm::Module> load_module(const std::string& str);
