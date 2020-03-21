#pragma once

#pragma once

#include <llvm/IR/Module.h>

#include <memory>

#define PARSE_TEST_MODULE(name, str)                                           \
  auto name = ::support::parse_module(str);                                    \
  REQUIRE(mod);

namespace support {

/**
 * Parse a Module from a string, or from stdin if no string is supplied.
 */
std::unique_ptr<llvm::Module> parse_module();
std::unique_ptr<llvm::Module> parse_module(std::string const& str);

/**
 * Load a Module from a file stored on disk at the specified path.
 */
std::unique_ptr<llvm::Module> load_module(std::string const& path);

/**
 * Load a Module from the specified path, or if the path is equal to the second
 * argument, parse it from stdin instead.
 */
std::unique_ptr<llvm::Module>
load_or_parse_module(std::string const& path, std::string const& parse = "-");

} // namespace support
