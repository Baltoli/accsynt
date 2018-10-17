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

bool synthesizer::satisfies_examples(Function *cand) const
{
  auto wrap = call_wrapper{properties_.type_signature, 
                           *cand->getParent(), cand->getName()};

  for(auto [in, out] : examples_) {
    auto ret = wrap.call(in);

    if(ret != out.return_value || in != out.output_args) {
      return false;
    }
  }

  return true;
}

Function *synthesizer::generate()
{
  Function *cand = nullptr;

  for(auto i = 0u; i < attempts_ && !cand; ++i) {
    cand = candidate();
    if(!satisfies_examples(cand)) {
      cand->eraseFromParent();
      cand = nullptr;
    }
  }

  return cand;
}

std::string null_synth::name() const
{
  return "Null";
}

Function *null_synth::generate()
{
  return nullptr;
}

}
