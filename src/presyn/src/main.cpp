#include "fragment.h"
#include "options.h"
#include "sketch.h"

#include <fmt/format.h>

#include <support/assert.h>
#include <support/terminal.h>

#include <props/props.h>

using namespace llvm;
using namespace presyn;
using namespace presyn::literals;
using namespace props;
using namespace props::literals;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  /* fmt::print("{}\n", opt::SigFile); */

  auto frag = "fixed<@x, 16>(seq(if(linear<0>), loop))"_frag;
  auto sig = "void func(float *x)"_sig;

  fmt::print("{}\n", *frag);
  fmt::print("{}\n", sig);

  auto sk = sketch(sig, *frag);
}
