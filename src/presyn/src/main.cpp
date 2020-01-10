#include "fragment.h"
#include "options.h"
#include "sketch.h"

#include <fmt/format.h>

#include <support/assert.h>
#include <support/llvm_format.h>
#include <support/terminal.h>

#include <props/props.h>

using namespace support;
using namespace llvm;
using namespace presyn;
using namespace presyn::literals;
using namespace props;
using namespace props::literals;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  /* fmt::print("{}\n", opt::SigFile); */

  auto frag = "seq(empty, seq(linear<10>, empty))"_frag;
  auto sig = "void func(float *x)"_sig;

  fmt::print("{}\n", *frag);
  fmt::print("{}\n", sig);

  auto sk = sketch(sig, *frag);

  fmt::print("\n{}", sk.module());
}
