#include "options.h"

#include <props/props.h>

#include <support/call_wrapper.h>
#include <support/dynamic_library.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

int main(int argc, char** argv)
{
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);
}
