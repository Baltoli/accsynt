#pragma once

#include <llvm/Support/CommandLine.h>

extern llvm::cl::opt<int> MaxFragments;
extern llvm::cl::opt<bool> DumpControl;
extern llvm::cl::opt<bool> CountControl;
extern llvm::cl::opt<std::string> ControlOutputFile;
extern llvm::cl::opt<bool> AllPrograms;
extern llvm::cl::opt<std::string> FragmentHash;
extern llvm::cl::opt<bool> InteractiveCount;
extern llvm::cl::opt<bool> NewRules;
extern llvm::cl::opt<bool> DryRun;
extern llvm::cl::opt<int> NumExamples;
extern llvm::cl::alias NumExamplesA;
extern llvm::cl::opt<bool> ShowStructureCode;
extern llvm::cl::opt<int> Sample;
