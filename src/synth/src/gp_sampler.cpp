#include "gp_sampler.h"

#include <support/random.h>
#include <support/tuple.h>

#include <llvm/Support/raw_ostream.h>

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

gp_sampler::gp_sampler(evaluator const& e)
    : eval_(e)
{
}

void gp_sampler::sample(int n, property_set ps, compile_metadata& meta) const
{
  auto ops = operations();

  auto total_weight = 0;
  ::support::for_each(ops, [&](auto& op) { total_weight += op.weight; });

  for (int i = 0; i < n; ++i) {
    auto running = 0;
    auto done = false;
    auto thresh = random_int(0, total_weight);

    ::support::for_each(ops, [&](auto& op) {
      running += op.weight;

      if (running >= thresh && !done) {
        op(meta);
        done = true;
      }
    });
  }
}

} // namespace synth
