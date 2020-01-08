#include "fragment.h"
#include "options.h"

#include <fmt/format.h>

#include <support/assert.h>
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

  auto str
      = "seq(seq(seq, seq(linear<2>, seq(linear<3>, linear<2>))), linear<2>)";

  auto frag = fragment::parse(str);
  assertion(frag != nullptr, "Fragment parse invalid");

  fmt::print("{}\n", frag->to_string());

  auto f2 = fragment::parse(frag->to_string());
  fmt::print("{}\n", f2->to_string());
}
