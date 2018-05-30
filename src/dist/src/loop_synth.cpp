#include <dist/loop_synth.h>

using namespace llvm;

namespace accsynt {

IRLoop::IRLoop(
    Function *f, 
    Loop l, 
    std::set<Value *> avail, 
    const BasicBlock *err,
    std::map<long, Value *> const& sizes,
    std::vector<std::set<long>> const& c,
    std::vector<Value *> p
) 
  : func_(f), loop_(l), sizes_(sizes), 
    coalesced_(c), available_(avail), parent_iters_(p),
    error_block_(err)
{
  // Need to lay out the first half of the loop body before laying out the
  // children! Then the contents of the pre-body can be available to the
  // children properly when they're laid out.
  if(l.is_instantiated()) {
    construct_loop();
  } else {
    construct_sequence();
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

void IRLoop::layout_children(Value *parent_iter)
{
  auto iters = [&] {
    if(parent_iter) {
      auto prev = parent_iters_;
      prev.push_back(parent_iter);
      return prev;
    } else {
      return parent_iters_;
    }
  }();

  for(auto const& child : loop_) {
    auto const& last = children_.emplace_back(
      func_, *child, available_, error_block_, sizes_, coalesced_, iters
    );

    std::copy(last.available_.begin(), last.available_.end(), 
              std::inserter(available_, available_.begin()));
  }
}

Value *IRLoop::make_iterator()
{
  auto id = *loop_.ID();

  auto iter_ty = IntegerType::get(func_->getContext(), 64);
  auto B = IRBuilder<>(pre_body_);
  auto iter = B.CreatePHI(iter_ty, 2);
  iter->addIncoming(B.getInt64(0), header_);

  B.SetInsertPoint(post_body_);
  auto next = B.CreateAdd(iter, B.getInt64(1));
  iter->addIncoming(next, post_body_);
  auto size = sizes_.at(id);
  auto cmp = B.CreateICmpEQ(next, size);
  B.CreateCondBr(cmp, exit_, pre_body_);

  return iter;
}

void IRLoop::construct_loop()
{
  auto id = *loop_.ID();
  
  // We have an outer loop ID here, so we need to create header blocks etc for
  // ourself using the information provided.
  auto make_block = [&] (std::string name) {
    return BasicBlock::Create(func_->getContext(), name + "_" + std::to_string(id), func_);
  };

  header_ = make_block("header");
  pre_body_ = make_block("pre_body");
  post_body_ = make_block("post_body");
  exit_ = make_block("exit");

  auto iter = make_iterator();

  auto meta = SynthMetadata{};
  meta.live(iter) = true;
  for(auto v : available_) {
    meta.live(v) = true;
  }

  auto B = IRBuilder<>(pre_body_);
  BlockGenerator(B, meta).populate(3);

  for(auto v : meta.live) {
    available_.insert(v);
  }

  layout_children(iter);

  for(auto v : available_) {
    meta.live(v) = true;
  }
  B.SetInsertPoint(post_body_->getTerminator());
  BlockGenerator(B, meta).populate(3);

  BranchInst::Create(pre_body_, header_);
  if(children_.empty()) {
    BranchInst::Create(post_body_, pre_body_);
  } else {
    BranchInst::Create(children_.begin()->header(), pre_body_);
    BranchInst::Create(post_body_, children_.rbegin()->exit());
  }
}

void IRLoop::construct_sequence()
{
  layout_children();
  // We don't have an outer loop ID, so we just lay out all the children in
  // sequence and set the header and exit to the respective blocks on the
  // first / last child.
  if(!children_.empty()) {
    header_ = children_.begin()->header_;
    exit_ = children_.rbegin()->exit_;
  }
}

Value *IRLoop::create_valid_sized_gep(
  IRBuilder<>& b, Value *data, Value *idx, 
  Value *size, BasicBlock *err) const
{
  auto ptr_ty = cast<PointerType>(data->getType());
  auto el_ty = ptr_ty->getElementType();

  auto ret = [&] {
    if(isa<ArrayType>(el_ty)) {
      return b.CreateGEP(data, {b.getInt64(0), idx});
    } else {
      return b.CreateGEP(data, idx);
    }
  }();

  auto current_block = b.GetInsertBlock();
  auto post_gep = current_block->splitBasicBlock(current_block->getTerminator());

  current_block->getTerminator()->eraseFromParent();
  b.SetInsertPoint(current_block);
  auto cond = b.CreateICmpUGE(idx, size);
  b.CreateCondBr(cond, err, post_gep);

  b.SetInsertPoint(post_gep->getTerminator());
  
  return ret;
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
