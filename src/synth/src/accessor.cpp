#include "accessor.h"

using namespace llvm;

namespace synth {

std::set<Value *> accessor::create_geps(
    compile_metadata const& meta,
    Value *index, Value *base, 
    IRBuilder<>& builder) const
{
  auto mapped = map_index(meta, index);
  auto geps = std::set<Value *>{};

  for(auto idx : mapped) {
    geps.insert(builder.CreateGEP(base, idx));
  }

  return geps;
}

// Default implementation that other accessors can override if needed
std::set<Value *> accessor::map_index(
    compile_metadata const& meta, Value* index) const
{
  return { index };
}

accessor_map::accessor_map() :
  accessor_map(accessor_map::backing_map_t{})
{
}

accessor_map::accessor_map(accessor_map::backing_map_t&& map) :
  backing_map_(std::move(map)),
  default_accessor_()
{
}

accessor const& accessor_map::operator()(std::string name) const
{
  if(backing_map_.find(name) != backing_map_.end()) {
    return *backing_map_.at(name);
  } else {
    return default_accessor_;
  }
}

}
