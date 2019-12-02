#include "options.h"

#include <fmt/format.h>

using namespace llvm;
using namespace presyn;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  fmt::print("{}\n", opt::SigFile);
}
