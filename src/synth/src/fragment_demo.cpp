#include "fragment.h"
#include "linear_fragment.h"

#include <props/props.h>
#include <support/thread_context.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <iostream>

using namespace props;
using namespace support;
using namespace synth;

using namespace llvm;

int main()
{
  auto sig = signature::parse("int func(int n, float *x)");
  auto mod = Module{"fragtest", thread_context::get()};

  auto ctx = compile_context{mod, sig};
  auto frag = linear_fragment{{}};

  frag.print(std::cout);
}
