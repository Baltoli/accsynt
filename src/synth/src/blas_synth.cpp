#include "synthesizer.h"

#include <fmt/format.h>

using namespace props;

namespace synth {

blas_synth::blas_synth(property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref),
  generator_(ps), examples_()
{
  auto limit = 1000;
  for(auto i = 0; i < limit; ++i) {
    auto cb = ref.get_builder();
    generator_.generate(cb);
    auto before = cb;
    auto ret = ref.call(cb);
    examples_.push_back({before, {ret, cb}});
  }
}

std::string blas_synth::name() const
{
  return "BLAS";
}

llvm::Function *blas_synth::generate() const
{
  return nullptr;
}

}
