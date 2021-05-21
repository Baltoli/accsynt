#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<std::string> InputFile;
extern llvm::cl::opt<std::string> FunctionName;
extern llvm::cl::opt<std::string> ManifestPath;
extern llvm::cl::opt<int> NumInputs;
extern llvm::cl::opt<int> Reps;
extern llvm::cl::opt<bool> Header;
extern llvm::cl::opt<bool> Single;
extern llvm::cl::opt<bool> Progress;
