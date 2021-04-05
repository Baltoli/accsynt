#pragma once

#include <llvm/Support/CommandLine.h>

enum PerfMode { Random, LinearSpace };

extern llvm::cl::opt<PerfMode> Mode;

extern llvm::cl::opt<std::string> PropertiesPath;
extern llvm::cl::opt<std::string> LibraryPath;
extern llvm::cl::opt<std::string> Tag;
extern llvm::cl::list<std::string> Parameters;

extern llvm::cl::opt<int> Start;
extern llvm::cl::opt<int> End;
extern llvm::cl::opt<int> Step;
extern llvm::cl::opt<int> Values;
extern llvm::cl::opt<int> Reps;

extern llvm::cl::opt<int> Min;
extern llvm::cl::opt<int> Max;
extern llvm::cl::opt<int> Independent;

extern llvm::cl::opt<int> MemSize;
