#pragma once

#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>

#include <set>

namespace interfind {

/**
 * Collect all the values that satisfy pred.
 */
namespace detail {

template <typename Pred>
class predicate_visitor : public llvm::InstVisitor<predicate_visitor<Pred>> {
  public:
  predicate_visitor(Pred);
  std::set<llvm::Value*> values() const;

  void visitInstruction(llvm::Instruction& inst);

  template <typename Range> void visitValues(Range&&);

  private:
  Pred pred_;
  std::set<llvm::Value*> vals_;
};

template <typename Pred>
predicate_visitor<Pred>::predicate_visitor(Pred p)
    : pred_(p)
    , vals_{}
{
}

template <typename Pred>
std::set<llvm::Value*> predicate_visitor<Pred>::values() const
{
  return vals_;
}

template <typename Pred>
void predicate_visitor<Pred>::visitInstruction(llvm::Instruction& inst)
{
  if (pred_(inst)) {
    vals_.insert(&inst);
  }

  for (auto& op : inst.operands()) {
    if (auto* cst = llvm::dyn_cast<llvm::Constant>(&op)) {
      if (pred_(*cst)) {
        vals_.insert(cst);
      }
    }
  }
}

template <typename Pred>
template <typename Range>
void predicate_visitor<Pred>::visitValues(Range&& rng)
{
  for (auto& val : rng) {
    if (pred_(val)) {
      vals_.insert(&val);
    }
  }
}
}

template <typename Pred>
std::set<llvm::Value*> values_by_pred(llvm::Function& fn, Pred pred)
{
  auto vis = detail::predicate_visitor(pred);

  vis.visit(fn);
  vis.visitValues(fn.getParent()->globals());
  vis.visitValues(fn.args());

  return vis.values();
}

std::set<llvm::Value*> values_of_type(llvm::Function&, llvm::Type*);
}
