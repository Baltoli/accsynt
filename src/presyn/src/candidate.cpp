#include "candidate.h"
#include "filler.h"
#include "sketch.h"

#include <support/assert.h>
#include <support/narrow_cast.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <algorithm>
#include <map>
#include <set>

using namespace llvm;

namespace presyn {

candidate::candidate(sketch&& sk, std::unique_ptr<filler> fill)
    : candidate(sk.ctx_.signature(), std::move(sk.module_), std::move(fill))
{
}

candidate::candidate(
    props::signature sig, std::unique_ptr<Module>&& mod,
    std::unique_ptr<filler> fill)
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

Module& candidate::module() { return *module_; }
Module const& candidate::module() const { return *module_; }

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

  stub_visitor([&, this](auto& ci) {
    if (ci.arg_size() != 1) {
      return;
    }

    if (auto name = arg_name(ci.getArgOperand(0))) {
      auto idx = signature_.param_index(*name);
      auto arg = function().arg_begin() + idx;

      replacements[&ci] = arg;
    }
  }).visit(function());

  for (auto [stub, val] : replacements) {
    auto conv = converter(val->getType(), stub->getType());

    auto build = IRBuilder(stub);
    auto call = build.CreateCall(conv, {val}, stub->getName());

    safe_rauw(stub, call);
  }
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

  auto replacements = std::map<CallInst*, Value*> {};

  operator_visitor([&, this](auto& ci) {
    if (auto op = create_operation(ci)) {
      replacements[&ci] = op;
    }
  }).visit(function());

  for (auto [stub, val] : replacements) {
    auto conv = converter(val->getType(), stub->getType());

    auto build = IRBuilder(stub);
    auto call = build.CreateCall(conv, {val}, stub->getName());

    safe_rauw(stub, call);
  }
}

bool candidate::is_valid() const
{
  auto vis = is_valid_visitor();
  vis.visit(function());
  return vis.valid();
}

std::optional<std::string> candidate::arg_name(llvm::Value* arg) const
{
  if (auto const_val = dyn_cast<ConstantDataArray>(arg)) {
    auto arr_t = const_val->getType();
    if (arr_t->getElementType()->isIntegerTy(8)) {
      auto str = std::vector<char> {};

      for (auto i = 0; i < arr_t->getNumElements(); ++i) {
        auto elt = const_val->getAggregateElement(i);
        auto chr = ::support::narrow_cast<char>(
            elt->getUniqueInteger().getSExtValue());
        str.push_back(chr);
      }

      return std::string(str.begin(), str.end());
    }
  }

  return std::nullopt;
}

llvm::Function* candidate::converter(llvm::Type* from, llvm::Type* to)
{
  // This allows us to get rid of the opaque struct type where usages of it
  // remain in the code - if any of these stubs try to produce an opaque struct
  // type, then we assume that the resulting type is precisely what it's being
  // converted from.
  if (auto ptr_to = dyn_cast<PointerType>(to)) {
    if (auto elt_st = dyn_cast<StructType>(ptr_to->getElementType())) {
      if (elt_st->isOpaque()) {
        to = from;
      }
    }
  }

  if (converters_.find({from, to}) == converters_.end()) {
    auto func_ty = FunctionType::get(to, {from}, false);
    auto func = Function::Create(
        func_ty, GlobalValue::InternalLinkage, "id", *module_);

    auto bb = BasicBlock::Create(module_->getContext(), "entry", func);
    auto build = IRBuilder(bb);

    llvm::Value* ret_val = func->arg_begin();

    assertion(
        to->isPointerTy() == from->isPointerTy(),
        "Can't convert between pointer and non-pointer");

    if (from != to) {
      if (to->isPointerTy()) {
        ret_val = build.CreatePointerCast(ret_val, to);
      } else if (from->isIntegerTy() && to->isIntegerTy()) {
        auto from_int = cast<IntegerType>(from);
        auto to_int = cast<IntegerType>(to);

        if (from_int->getBitWidth() < to_int->getBitWidth()) {
          ret_val = build.CreateSExt(ret_val, to);
        } else {
          ret_val = build.CreateTruncOrBitCast(ret_val, to);
        }
      }
    }

    build.CreateRet(ret_val);

    converters_[{from, to}] = func;
  }

  return converters_.at({from, to});
}

void candidate::safe_rauw(Instruction* stub, Value* call)
{
  auto replacements = std::map<Instruction*, Value*> {};

  if (call->getType() == stub->getType()) {
    stub->replaceAllUsesWith(call);
  } else {
    // Different types so we need to recreate every stub call that *uses* the
    // result of this one separately.

    for (auto user : stub->users()) {
      assertion(
          isa<CallInst>(user) || isa<PHINode>(user),
          "Users of stub calls must be calls or PHIs");

      if (auto user_call = dyn_cast<CallInst>(user)) {
        auto new_args = std::vector<Value*> {};
        for (auto& arg : user_call->args()) {
          new_args.push_back(arg == stub ? call : arg);
        }

        auto new_call = IRBuilder(stub).CreateCall(
            user_call->getCalledFunction(), new_args, stub->getName());

        replacements[user_call] = new_call;

      } else if (auto user_phi = dyn_cast<PHINode>(user)) {
        auto new_phi = IRBuilder(stub).CreatePHI(
            call->getType(), user_phi->getNumIncomingValues(),
            user_phi->getName());

        for (auto& val : user_phi->incoming_values()) {
          // assert this is a call ? edge cases
          auto incoming_call = cast<CallInst>(val);
          auto typed_call = update_type(incoming_call, call->getType());

          replacements[incoming_call] = typed_call;
        }

        // how to now RAUW a phi node???
      } else {
        invalid_state();
      }
    }
  }

  for (auto [st, ca] : replacements) {
    safe_rauw(st, ca);
  }

  stub->eraseFromParent();
}

CallInst* candidate::update_type(CallInst* stub, Type* type)
{
  unimplemented();
  ;
}

} // namespace presyn
