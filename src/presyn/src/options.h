#pragma once

#include <llvm/Support/CommandLine.h>

#include <string>

namespace presyn::opt {

extern llvm::cl::opt<std::string> SigFile;

}
