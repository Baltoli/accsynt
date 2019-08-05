#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<int> MaxFragments;
extern llvm::cl::opt<bool> DumpControl;
extern llvm::cl::opt<bool> AllPrograms;
extern llvm::cl::opt<std::string> FragmentHash;
extern llvm::cl::opt<bool> InteractiveCount;
