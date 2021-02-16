#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<std::string> PropertiesPath;
extern llvm::cl::opt<std::string> LibraryPath;
extern llvm::cl::opt<std::string> Parameter;

extern llvm::cl::opt<int> Start;
extern llvm::cl::opt<int> End;
extern llvm::cl::opt<int> Step;
extern llvm::cl::opt<int> Reps;

extern llvm::cl::opt<int> MemSize;
