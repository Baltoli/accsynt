#include "candidate.h"

#include <support/assert.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <algorithm>
#include <map>

using namespace llvm;

namespace {

// Generic stub visitor

template <typename Func>
class stub_visitor : public InstVisitor<stub_visitor<Func>> {
public:
  stub_visitor(Func&&);

  void visitCallInst(CallInst const&) const;

private:
  Func action_;
};

template <typename Func>
stub_visitor<Func>::stub_visitor(Func&& f)
    : action_(std::forward<Func>(f))
{
}

template <typename Func>
void stub_visitor<Func>::visitCallInst(CallInst const& inst) const
{
  auto fn = inst.getCalledFunction();
  auto name = fn->getName();
  if (name.startswith("stub")) {
    action_(inst);
  }
}

// Validation visitor

class is_valid_visitor : public InstVisitor<is_valid_visitor> {
public:
  is_valid_visitor() = default;

  bool valid() const;

  void visitCallInst(CallInst const&);

private:
  bool valid_ = true;
};

bool is_valid_visitor::valid() const { return valid_; }

void is_valid_visitor::visitCallInst(CallInst const& ci)
{
  auto fn = ci.getCalledFunction();
  if (fn->isDeclaration()) {
    valid_ = false;
  }
}

} // namespace

namespace presyn {

candidate::candidate(props::signature sig, std::unique_ptr<Module>&& mod)
    : signature_(sig)
    , module_(std::move(mod))
{
  resolve_names();
  choose_values();
  resolve_operators();
}

Function& candidate::function() const
{
  auto func = module_->getFunction(signature_.name);
  assertion(func != nullptr, "Must have correctly named candidate function");
  return *func;
}

void candidate::resolve_names()
{
  // The process for resolving stubbed-out names in the generated sketch is as
  // follows:
  //  - for all the call insts in the function, look at their name and argument
  //    list.
  //  - if they have a name like 'stub', and their only argument is a constant
  //    character array, then de-materialize it to a string and look up the
  //    param with that name in the sig.
  //  - delete the stub, and replace it with the named argument
  //
  //  For all these things we need an instvisitor really - will save writing all
  //  the loops over and over.

  auto replacements = std::map<CallInst*, Value*> {};

  stub_visitor([&, this](auto const& ci) {
    if (ci.arg_size() != 1) {
      return;
    }

    if (auto name = arg_name(ci.getArgOperand(0))) {
      auto idx = signature_.param_index(*name);
      auto arg = function().arg_begin() + idx;
      arg->dump();
    }
  }).visit(function());
}

void candidate::choose_values()
{
  // After resolving the named stubs in the function, the next step in the
  // candidate construction process is to select values for all the stubs in the
  // program.
  //
  // Worth noting that this will involve some kind of non-determinism (as random
  // choices will have to be made), so it's probably worth considering from the
  // beginning how to get it to be controllable. For a given sketch, the set of
  // available decisions will always be the same, so we can try to record which
  // ones are made so that branches / near misses / introspection are possible.
}

void candidate::resolve_operators()
{
  // After values are chosen for the stubbed out values in the function, the
  // operators can be resolved - this step will involve some thought about the
  // types of the values being used (as by now we'll know the types).
}

bool candidate::is_valid() const
{
  auto vis = is_valid_visitor();
  vis.visit(function());
  return vis.valid();
}

std::optional<std::string> candidate::arg_name(llvm::Value*) const
{
  return "fkopefw";
}

} // namespace presyn
