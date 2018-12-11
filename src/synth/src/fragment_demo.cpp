#include "fragment.h"
#include "linear_fragment.h"
#include "regular_loop_fragment.h"

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

  auto f1 = regular_loop_fragment{{
    value::with_param("x"), value::with_param("n")
  }};

  auto choices = std::vector<fragment::frag_ptr>{};
  choices.push_back(f1.clone());

  auto all = fragment::enumerate(std::move(choices), 3);

  for(auto& f : all) {
    errs() << "\u001b[41;1m" 
           << "########  Example  ########"
           << "\u001b[0m\n\n";
    errs() << "\u001b[44;1m"
           << "Version:"
           << "\u001b[0m\n";

    errs() << f->to_str(0) << "\n\n";

    auto data = f->compile(ctx);
    errs() << "\u001b[42;1m"
           << "Code:"
           << "\u001b[0m";
    errs() << *data.function << '\n';
  }

  /* frag.add_child(empty_fragment{{}}); */
  /* frag.add_child(frag.clone()); */
  /* frag.add_child(empty_fragment{{}}); */
  /* frag.add_child(linear_fragment{{}}); */

  /* frag.print(std::cout); */

  /* auto data = frag.compile(ctx); */
  /* errs() << *data.function << '\n'; */

  /* errs() << "After compilation:\n"; */

  /* errs() << "Data blocks:\n"; */
  /* for(auto block : data.data_blocks) { */
  /*   errs() << "\t" << block->getName() << '\n'; */
  /* } */

  /* errs() << "Seeds:\n"; */
  /* for(auto seed : data.seeds) { */
  /*   errs() << "\t" << *seed << '\n'; */
  /* } */

  /* errs() << "Outputs:\n"; */
  /* for(auto out : data.outputs) { */
  /*   errs() << "\t" << *out << '\n'; */
  /* } */
}
