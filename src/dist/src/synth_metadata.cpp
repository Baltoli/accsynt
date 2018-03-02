#include <dist/synth_metadata.h>

std::optional<size_t> SynthMetadata::index_bound(llvm::Value *v) const
{
  if(auto b = bounds_.find(v); b != std::end(bounds_)) {
    return b->second;
  } else {
    return {};
  }
}

bool SynthMetadata::is_index(llvm::Value *v) const
{
  return bounds_.find(v) != std::end(bounds_);
}

void SynthMetadata::set_index_bound(llvm::Value *v, size_t b)
{
  bounds_.insert_or_assign(v, b);
}

void SynthMetadata::make_live(llvm::Value *v)
{
  live_set_.insert(v);
}


void SynthMetadata::make_oob_flag(llvm::Value *v)
{
  oob_flags_.insert(v);
}
