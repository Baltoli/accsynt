#pragma once

#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instructions.h>

namespace presyn {

// Generic stub visitor

template <typename Func>
class stub_visitor : public llvm::InstVisitor<stub_visitor<Func>> {
public:
  stub_visitor(Func&&);

  void visitCallInst(llvm::CallInst&) const;

private:
  Func action_;
};

template <typename Func>
stub_visitor<Func>::stub_visitor(Func&& f)
    : action_(std::forward<Func>(f))
{
}

template <typename Func>
void stub_visitor<Func>::visitCallInst(llvm::CallInst& inst) const
{
  auto fn = inst.getCalledFunction();
  auto name = fn->getName();
  if (name.startswith("stub")) {
    action_(inst);
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
