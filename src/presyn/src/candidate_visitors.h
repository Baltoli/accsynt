#pragma once

#include <llvm/IR/CFG.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instructions.h>

#include <queue>
#include <set>

namespace presyn {

// Generic stub visitor

template <typename Func>
class stub_visitor {
public:
  stub_visitor(Func&&);

  void visit(llvm::Function& f);

  /* void visitCallInst(llvm::CallInst&) const; */

private:
  Func action_;
};

template <typename Func>
stub_visitor<Func>::stub_visitor(Func&& f)
    : action_(std::forward<Func>(f))
{
}

// This needs to be a custom implementation so that we can iterate in top-down
// order selecting values later on - the ordering shouldn't make a difference to
// consumers who don't care.
template <typename Func>
void stub_visitor<Func>::visit(llvm::Function& f)
{
  auto work = std::queue<llvm::BasicBlock*> {};
  auto done_set = std::set<llvm::BasicBlock*> {};

  auto& entry = f.getEntryBlock();
  work.push(&entry);

  while (!work.empty()) {
    auto bb = work.front();
    work.pop();

    if (done_set.find(bb) != done_set.end()) {
      continue;
    }

    for (auto& inst : *bb) {
      if (auto ci = llvm::dyn_cast<llvm::CallInst>(&inst)) {
        auto fn = ci->getCalledFunction();
        auto name = fn->getName();
        if (name.startswith("stub")) {
          action_(*ci);
        }
      }
    }

    done_set.insert(bb);
    for (auto it = llvm::succ_begin(bb); it != llvm::succ_end(bb); ++it) {
      work.push(*it);
    }
  }
}

// Operator visitor

template <typename Func>
class operator_visitor : public llvm::InstVisitor<operator_visitor<Func>> {
public:
  operator_visitor(Func&&);

  void visitCallInst(llvm::CallInst&) const;

private:
  Func action_;
};

template <typename Func>
operator_visitor<Func>::operator_visitor(Func&& f)
    : action_(std::forward<Func>(f))
{
}

template <typename Func>
void operator_visitor<Func>::visitCallInst(llvm::CallInst& inst) const
{
  auto fn = inst.getCalledFunction();
  auto name = fn->getName();
  if (name.startswith("__")) {
    action_(inst);
  }
}

// Validation visitor

class is_valid_visitor : public llvm::InstVisitor<is_valid_visitor> {
public:
  is_valid_visitor() = default;

  bool valid() const;

  void visitCallInst(llvm::CallInst const&);

private:
  bool valid_ = true;
};

} // namespace presyn
