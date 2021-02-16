#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<std::string> PropertiesPath;
extern llvm::cl::opt<std::string> LibraryPath;

extern llvm::cl::opt<int> MemSize;
