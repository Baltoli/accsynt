#pragma once

#include <llvm/Support/CommandLine.h>

#include <string>

namespace presyn::oracle::opts {

extern llvm::cl::opt<std::string> InputFilename;

}
