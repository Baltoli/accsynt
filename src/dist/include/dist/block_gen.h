#pragma once

#include <dist/synth_metadata.h>

namespace accsynt {

template <typename Builder>
class BlockGenerator {
public:
  BlockGenerator(Builder& b, SynthMetadata& m) :
    b_(b), meta_(m)
  {}

  void populate(size_t n_instrs);

private:
  Builder& b_;
  SynthMetadata& meta_;
};

template <typename Builder>
void BlockGenerator<Builder>::populate(size_t n_instrs)
{
}

}
