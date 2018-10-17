#include "synthesizer.h"

#include "generator.h"

using namespace props;
using namespace llvm;

namespace synth {

synthesizer::synthesizer(props::property_set ps, call_wrapper& wrap)
  : properties_(ps), reference_(wrap),
    examples_()
{
}

void synthesizer::make_examples(generator& gen, size_t n)
{
  for(auto i = 0u; i < n; ++i) {
    auto cb = reference_.get_builder();
    gen.generate(cb);
    auto before = cb;
    auto ret = reference_.call(cb);
    examples_.push_back({before, {ret, cb}});
  }
}

std::string null_synth::name() const
{
  return "Null";
}

Function *null_synth::generate()
{
  auto build = reference_.get_builder();

  auto gen = blas_generator(properties_);
  gen.generate(build);

  auto ret = reference_.call(build);
  errs() << ret << '\n';
  return nullptr;
}

}
