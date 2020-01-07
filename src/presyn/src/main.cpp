#include "fragment.h"
#include "options.h"

#include <fmt/format.h>

#include <support/terminal.h>

using namespace llvm;
using namespace presyn;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  /* fmt::print("{}\n", opt::SigFile); */

  /* std::unique_ptr<fragment> frag = std::make_unique<presyn::empty>(); */

  /* frag = frag->compose(presyn::empty()); */
  /* frag = frag->compose(presyn::seq()); */
  /* frag = frag->compose( */
  /*     presyn::linear(std::make_unique<presyn::constant_int>(2))); */
  /* frag = frag->compose( */
  /*     presyn::linear(std::make_unique<presyn::constant_int>(4))); */

  /* fmt::print("{}\n", frag->to_string()); */

  auto frag = fragment::parse("linear(empty, seq<4>(linear, empty))");
}
