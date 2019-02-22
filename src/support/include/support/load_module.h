#pragma once

#pragma once

#include <llvm/IR/Module.h>

#include <memory>

#define PARSE_TEST_MODULE(name, str)                                           \
  auto name = ::support::parse_module(str);                                    \
  REQUIRE(mod);

namespace support {

std::unique_ptr<llvm::Module> parse_module(std::string const& str);

std::unique_ptr<llvm::Module> load_module(std::string const& path);
}
