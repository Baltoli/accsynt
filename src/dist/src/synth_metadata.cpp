#include <dist/synth_metadata.h>

std::optional<size_t> SynthMetadata::index_bound(llvm::Value *v) const
{
  if(auto b = bounds_.find(v); b != std::end(bounds_)) {
    return b->second;
  } else {
    return {};
  }
}

void SynthMetadata::set_index_bound(llvm::Value *v, size_t b)
{
  bounds_.insert_or_assign(v, b);
}
