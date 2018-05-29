#include <dist/loop_synth.h>

using namespace llvm;

namespace accsynt {

IRLoop::IRLoop(llvm::Function *f, Loop l, std::set<Value *> avail) :
  available_(avail)
{
  if(l.is_instantiated()) {
    // We have an outer loop ID here, so we need to create header blocks etc for
    // ourself using the information provided.
  } else {
    // We don't have an outer loop ID, so we just lay out all the children in
    // sequence and set the header and exit to the respective blocks on the
    // first / last child.
    for(auto const& child : l) {
      auto const& last = children_.emplace_back(f, *child, available_);
      std::copy(last.available_.begin(), last.available_.end(), 
                std::inserter(available_, available_.begin()));
    }
    
    if(!children_.empty()) {
      header_ = children_.begin()->header_;
      exit_ = children_.rbegin()->exit_;
    }
  }
}

std::set<Value *> const& IRLoop::available_values() const
{
  return available_;
}

llvm::BasicBlock *const IRLoop::header() const
{
  return header_;
}

llvm::BasicBlock *const IRLoop::pre_body() const
{
  return pre_body_;
}

std::vector<IRLoop> const& IRLoop::children() const
{
  return children_;
}

llvm::BasicBlock *const IRLoop::post_body() const
{
  return post_body_;
}

llvm::BasicBlock *const IRLoop::exit() const
{
  return exit_;
}

}
