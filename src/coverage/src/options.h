#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<std::string> InputFile;
extern llvm::cl::opt<std::string> FunctionName;
extern llvm::cl::opt<int> NumInputs;
