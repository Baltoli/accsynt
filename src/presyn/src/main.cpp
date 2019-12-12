#include "fragment.h"
#include "options.h"

#include <fmt/format.h>

using namespace llvm;
using namespace presyn;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  /* fmt::print("{}\n", opt::SigFile); */

  std::unique_ptr<fragment> frag = std::make_unique<seq>();

  frag = frag->compose(std::make_unique<presyn::empty>());

  fmt::print("{}\n", frag->to_string());
}
