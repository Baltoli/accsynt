#pragma once

#include <dist/synth_metadata.h>
#include <dist/utils.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/raw_ostream.h>

namespace accsynt {

template <typename Builder>
class BlockGenerator {
public:
  BlockGenerator(Builder& b, SynthMetadata& m) :
    b_(b), meta_(m)
  {}

  void populate(size_t n_instrs);
  void output();

private:
  Builder& b_;
  SynthMetadata& meta_;
};

template <typename Builder>
void BlockGenerator<Builder>::populate(size_t n_instrs)
{
  for(auto i = 0u; i < n_instrs; ++i) {
    auto live = std::vector<llvm::Value *>{};

    auto v1 = uniform_sample(meta_.live);
    auto v2 = uniform_sample(meta_.live);

    assert(v1 != std::end(meta_.live) &&
           v2 != std::end(meta_.live) &&
           "Could not sample values to create add");
    auto add = b_.CreateAdd(*v1, *v2);
    auto mul = b_.CreateMul(*v1, *v2);
    
    live.push_back(add);
    live.push_back(mul);

    for(auto val : live) {
      meta_.live(val) = true;
    }
  }

  for(auto i = 0u; i < n_instrs; ++i) {
    auto v1 = uniform_sample(meta_.live);
    auto v2 = uniform_sample(meta_.live);

    assert(v1 != std::end(meta_.live) &&
           v2 != std::end(meta_.live) &&
           "Could not sample values to create add");
    auto add = b_.CreateAdd(*v1, *v2);
    auto mul = b_.CreateMul(*v1, *v2);
    
    meta_.live(add) = true;
    meta_.live(mul) = true;
  }
}

template <typename Builder>
void BlockGenerator<Builder>::output()
{
  auto store_output = [&](auto v) {
    // fix later perhaps if this might not be a pointer - any other way to
    // enforce responsible usage?
    auto ptr_ty = llvm::cast<llvm::PointerType>(v->getType());

    auto sample = uniform_sample_if(meta_.live, [&](auto val) {
      return val->getType() == ptr_ty->getElementType();
    });

    if(sample != std::end(meta_.live)) {
      auto value = *sample;
      b_.CreateStore(value, v);
    }
  };

  for(auto v : meta_.output) {
    store_output(v);
  }

  if(meta_.return_loc) {
    store_output(meta_.return_loc);
  }
}

}
