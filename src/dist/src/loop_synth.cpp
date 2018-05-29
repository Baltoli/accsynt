#include <dist/loop_synth.h>

using namespace llvm;

namespace accsynt {

IRLoop::IRLoop(llvm::Function *f, Loop l, std::set<Value *> avail, std::map<long, Value *> const& sizes) :
  sizes_(sizes), available_(avail)
{
  for(auto const& child : l) {
    auto const& last = children_.emplace_back(f, *child, available_, sizes);
    std::copy(last.available_.begin(), last.available_.end(), 
              std::inserter(available_, available_.begin()));
  }

  if(l.is_instantiated()) {
    construct_control_flow(f, *l.ID());
  } else {
    // We don't have an outer loop ID, so we just lay out all the children in
    // sequence and set the header and exit to the respective blocks on the
    // first / last child.
    if(!children_.empty()) {
      header_ = children_.begin()->header_;
      exit_ = children_.rbegin()->exit_;
    }
  }

  // Link sequential children together - create an unconditional branch from
  // each one to its successor.
  if(children_.size() > 1) {
    for(auto i = 0u; i < children_.size() - 1; ++i) {
      auto& first = children_.at(i);
      auto& second = children_.at(i + 1);

      BranchInst::Create(second.header(), first.exit());
    }
  }
}

void IRLoop::construct_control_flow(Function *f, long id)
{
  auto str_id = std::to_string(id);
  // We have an outer loop ID here, so we need to create header blocks etc for
  // ourself using the information provided.
  header_ = BasicBlock::Create(f->getContext(), "header_" + str_id, f);
  pre_body_ = BasicBlock::Create(f->getContext(), "pre_body_" + str_id, f);
  post_body_ = BasicBlock::Create(f->getContext(), "post_body_" + str_id, f);
  exit_ = BasicBlock::Create(f->getContext(), "exit_" + str_id, f);

  auto iter_ty = IntegerType::get(f->getContext(), 64);
  auto B = IRBuilder<>(pre_body_);
  auto iter = B.CreatePHI(iter_ty, 2);
  iter->addIncoming(B.getInt64(0), header_);

  B.SetInsertPoint(post_body_);
  auto next = B.CreateAdd(iter, B.getInt64(1));
  iter->addIncoming(next, post_body_);
  auto size = sizes_.at(id);
  auto cmp = B.CreateICmpEQ(next, size);
  B.CreateCondBr(cmp, exit_, pre_body_);

  BranchInst::Create(pre_body_, header_);
  if(children_.empty()) {
    BranchInst::Create(post_body_, pre_body_);
  } else {
    BranchInst::Create(children_.begin()->header(), pre_body_);
    BranchInst::Create(post_body_, children_.rbegin()->exit());
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
