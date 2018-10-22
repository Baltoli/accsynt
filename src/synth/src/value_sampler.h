#pragma once

#include <llvm/IR/Constant.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

namespace synth {

class value_sampler {
public:
  value_sampler() = default;

  template <typename Builder>
  void operator()(Builder&&, size_t, std::vector<llvm::Value *>&);

private:
  // Internal state kept during the generation process
};

template <typename Builder>
void value_sampler::operator()(Builder&& B, size_t n, 
                               std::vector<llvm::Value *>& live)
{
  if(!live.empty()) {
    // TODO: do this randomly
    // TODO: and do it the right number of times
    auto *val = live.at(0);
  }
}

}
