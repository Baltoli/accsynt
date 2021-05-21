#include <support/options.h>

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

int main(int argc, char** argv)
{
  hide_llvm_options();
  cl::ParseCommandLineOptions(argc, argv);
}
