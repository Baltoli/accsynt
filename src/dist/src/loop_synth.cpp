#include <dist/loop_synth.h>

using namespace llvm;

namespace accsynt {

IRLoop::IRLoop(Function *f, Loop const& l, 
               std::map<long, long> const& e,
               llvm::BasicBlock* post) :
  func_(f), post_loop_(post),
  shape_(l), extents_(e),
  B_(func_->getContext()),
  header(BasicBlock::Create(func_->getContext(), "header", func_)),
  body(BasicBlock::Create(func_->getContext(), "body", func_)),
  exit(BasicBlock::Create(func_->getContext(), "exit", func_))
{
  // set up the loop header
  B_.SetInsertPoint(header);
  auto end_idx = [&] {
    try {
      return B_.getInt64(extents_.at(shape_.ID()));
    } catch(...) {
      return B_.getInt64(1);
    }
  }();
  B_.CreateBr(body);

  // set up the loop body
  auto iter_ty = llvm::IntegerType::get(func_->getContext(), 64);
  B_.SetInsertPoint(body);
  auto iter = B_.CreatePHI(iter_ty, 2, "iter");
  iter->addIncoming(B_.getInt64(0), header);

  auto next = exit;
  for(auto it = shape_.rbegin(); it != shape_.rend(); ++it) {
    auto irl = IRLoop(func_, **it, extents_, next);
    next = irl.header;
  }
  B_.CreateBr(next);

  // Set up the loop exit and post-loop control flow
  B_.SetInsertPoint(exit);
  auto incr = B_.CreateAdd(iter, B_.getInt64(1));
  iter->addIncoming(incr, exit);
  auto cond = B_.CreateICmpEQ(incr, end_idx);
  B_.CreateCondBr(cond, post_loop_, body);

  B_.SetInsertPoint(post_loop_);
  post_loop_->moveAfter(exit);
}

}
