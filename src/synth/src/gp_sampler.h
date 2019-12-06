#pragma once

#include "compile_metadata.h"
#include "evaluator.h"

#include <props/props.h>

#include <llvm/IR/Function.h>

#include <tuple>

namespace synth {

template <typename F>
struct gp_op {
  int weight;
  F op;

  gp_op(int w, F o)
      : weight(w)
      , op(o)
  {
  }

  gp_op(F o)
      : gp_op(1, o)
  {
  }

  void operator()(compile_metadata& c) { op(c); }
};

// clang-format off
inline auto operations() { 
  return std::tuple{
  }; 
}
// clang-format on

class gp_sampler {
public:
  gp_sampler(evaluator const&);

  void sample(int, props::property_set, compile_metadata&) const;
};

} // namespace synth
