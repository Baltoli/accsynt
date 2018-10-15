#include "synthesizer.h"

#include "generator.h"

using namespace props;
using namespace llvm;

namespace synth {

synthesizer::synthesizer(props::property_set ps, call_wrapper& wrap)
  : properties_(ps), reference_(wrap)
{
}

std::string null_synth::name() const
{
  return "Null";
}

Function *null_synth::generate() const
{
  auto build = reference_.get_builder();

  auto gen = blas_generator(properties_);
  gen.generate(build);

  auto ret = reference_.call(build);
  errs() << ret << '\n';
  return nullptr;
}

}
