#include "accessor.h"

#include <llvm/IR/Constants.h>

using namespace llvm;

namespace synth {

std::set<Value*> accessor::create_geps(compile_metadata const& meta,
    Value* index, Value* base, IRBuilder<>& builder,
    std::string const& prefix) const
{
  auto mapped = map_index(meta, index, builder);
  auto geps = std::set<Value*>{};

  for (auto idx : mapped) {
    geps.insert(builder.CreateGEP(base, idx, prefix));
  }

  return geps;
}

// Default implementation that other accessors can override if needed
std::set<Value*> accessor::map_index(
    compile_metadata const& meta, Value* index, IRBuilder<>&) const
{
  return { index };
}

std::set<Value*> offset_accessor::map_index(
    compile_metadata const& meta, Value* index, IRBuilder<>& builder) const
{
  auto idx_ty = index->getType();
  auto offset
      = builder.CreateAdd(ConstantInt::get(idx_ty, 1), index, "offset.idx");
  return { offset };
}

std::set<Value*> paired_accessor::map_index(
    compile_metadata const& meta, Value* index, IRBuilder<>& builder) const
{
  auto idx_ty = index->getType();
  auto offset
      = builder.CreateAdd(ConstantInt::get(idx_ty, 1), index, "paired.idx");
  return { index, offset };
}

accessor_map::accessor_map()
    : accessor_map(accessor_map::backing_map_t{})
{
}

accessor_map::accessor_map(accessor_map::backing_map_t&& map)
    : backing_map_(std::move(map))
    , default_accessor_()
{
}

accessor const& accessor_map::operator()(std::string const& name) const
{
  if (backing_map_.find(name) != backing_map_.end()) {
    return *backing_map_.at(name);
  } else {
    return default_accessor_;
  }
}
} // namespace synth
