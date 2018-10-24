#include "synthesizer.h"

#include "generator.h"

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

synthesizer::synthesizer(props::property_set ps, call_wrapper& wrap)
  : properties_(ps), reference_(wrap),
    examples_(), mod_("synth", thread_context::get())
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

  int vvv = 0;
  for(auto [in, out] : examples_) {
    auto ret = wrap.call(in);
    ++vvv;
    // WHAT
    // Sometimes an example is just *WRONG* - why is this? It contains all
    // zeroes. Look at make_examples to see what breaks.

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

Function *synthesizer::create_stub()
{
  return properties_.type_signature.create_function(mod_);
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
