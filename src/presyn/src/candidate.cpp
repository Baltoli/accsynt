#include "candidate.h"
#include "filler.h"
#include "sketch.h"

#include <support/assert.h>
#include <support/llvm_format.h>
#include <support/narrow_cast.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Transforms/IPO/AlwaysInliner.h>

#include <algorithm>
#include <deque>
#include <map>
#include <set>

using namespace llvm;

namespace presyn {

candidate::candidate(sketch&& sk, std::unique_ptr<filler> fill)
    : filler_(std::move(fill))
    , signature_(sk.ctx_.signature())
    , module_(std::move(sk.module_))
    , hole_type_(sk.ctx_.opaque_type())
    , type_convs_()
    , ctx_(std::move(sk.ctx_))
{
  filler_->set_candidate(*this);

  type_convs_.register_opaque(hole_type());

  resolve_names();
  insert_phis();
  resolve_operators();
  inline_identities();
  choose_values();
  resolve_operators();

  hoist_phis();
}

sketch_context& candidate::ctx() { return ctx_; }

Type* candidate::hole_type() const { return hole_type_; }

Function& candidate::function()
{
  auto func = module_->getFunction(signature_.name);
  assertion(func != nullptr, "Must have correctly named candidate function");
  return *func;
}

Function const& candidate::function() const
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
  // TODO: this needs to fill holes in *dominance* order

  // After resolving the named stubs in the function, the next step in the
  // candidate construction process is to select values for all the stubs in the
  // program.
  //
  // We can't run this as a typical visitor pattern because we need to update
  // the IR after each replacement; we will need to update dependencies between
  // things when they get updated.
  //
  // This process is delegated to the filler object passed in at construction.

  auto holes = std::deque<CallInst*> {};

  stub_visitor([&holes](auto& ci) { holes.push_back(&ci); }).visit(function());

  while (!holes.empty()) {
    auto hole = holes.front();
    holes.pop_front();

    auto new_val = filler_->fill(hole);

    if (new_val) {
      // The filler returned a valid value
      auto conv = converter(new_val->getType(), hole->getType());

      auto build = IRBuilder(hole);
      auto call = build.CreateCall(conv, {new_val}, hole->getName());

      auto new_holes = safe_rauw(hole, call);
      for (auto nh : new_holes) {
        holes.push_back(nh);
      }

      if (filler_->is_hole(new_val)) {
        holes.push_front(cast<CallInst>(new_val));
      }
    } else {
      // No possible value returned by the filler - just delete the hole.
      hole->eraseFromParent();
    }
  }
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

void candidate::insert_phis(int n_per_type)
{
  // This is the first step in turning a sketch into a candidate program.
  // Sketches don't know how they're being composed, so can't necessarily insert
  // the appropriate Phi nodes to allow for control-dependent data flow.
  //
  // To solve this, we add an opaque Phi node to every block - later in the
  // refinement process we can select a type, and subsequently a concrete value
  // for each of these nodes.

  auto& func = function();

  for (auto& bb : func) {
    if (bb.hasNPredecessorsOrMore(2)) {
      // Don't need a Phi node if the BB has fewer than 2 preds
      auto n_preds = pred_size(&bb);
      auto first = bb.getFirstNonPHI();

      auto phi = PHINode::Create(hole_type(), n_preds, "join", first);

      for (auto pred : predecessors(&bb)) {
        auto end = pred->getTerminator();

        auto in_stub = ctx().stub();
        in_stub->setName("join.in");

        in_stub->insertBefore(end);
        phi->addIncoming(in_stub, pred);
      }
    }
  }

  hoist_phis();
}

void candidate::hoist_phis()
{
  for (auto& bb : function()) {
    [[maybe_unused]] auto first_non_phi = bb.getFirstNonPHI();

    for (auto& inst : bb) {
      // FIXME: when I get LLVM 11 working, check if the first_non_phi comes
      // before inst - if so, break out of the loop.

      if (auto as_phi = dyn_cast<PHINode>(&inst)) {
        as_phi->moveBefore(bb, bb.getFirstInsertionPt());
      }
    }
  }
}

void candidate::inline_identities()
{
  auto is_id = [](auto& func) {
    auto name_valid = func.getName().startswith("id");
    auto type = func.getFunctionType();

    auto type_valid = type->getNumParams() == 1
                      && type->getParamType(0) == type->getReturnType();

    return name_valid && type_valid;
  };

  for (auto& func : module()) {
    if (is_id(func)) {
      for (auto* use : func.users()) {
        auto ci = cast<CallInst>(use);
        ci->replaceAllUsesWith(ci->getArgOperand(0));
        ci->eraseFromParent();
      }
    }
  }
}

bool candidate::is_valid()
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

      for (auto i = 0u; i < arr_t->getNumElements(); ++i) {
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

    func->addFnAttr(Attribute::AlwaysInline);

    auto bb = BasicBlock::Create(module_->getContext(), "entry", func);
    auto build = IRBuilder(bb);

    llvm::Value* ret_val = func->arg_begin();

    assertion(
        to->isPointerTy() == from->isPointerTy(),
        "Can't convert between pointer and non-pointer (when converting {} to "
        "{})",
        *from, *to);

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

std::set<llvm::CallInst*> candidate::safe_rauw(Instruction* stub, Value* call)
{
  auto replacements = std::map<Instruction*, Value*> {};
  auto new_holes = std::set<CallInst*> {};

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
        auto new_phi = IRBuilder(user_phi).CreatePHI(
            call->getType(), user_phi->getNumIncomingValues(),
            user_phi->getName());

        for (auto i = 0u; i < user_phi->getNumIncomingValues(); ++i) {
          auto in_val = user_phi->getIncomingValue(i);
          auto in_block = user_phi->getIncomingBlock(i);

          // First step here is to make sure that every incoming value is
          // compatible with the new one's type.
          assertion(
              type_convs_.is_lossless(in_val->getType(), call->getType()),
              "Invalid type conversion when RAUW-NTing a Phi Node: {} => {}",
              *in_val->getType(), *call->getType());

          // We also need to check that the incoming value is actually a hole -
          // we can't yet go around changing the type of arbitrary things.
          assertion(
              filler_->is_hole(in_val),
              "Can't change non-hole incoming value to a Phi: {}", *in_val);

          auto in_call = cast<CallInst>(in_val);

          // Now we know that we can safely convert the types, so go ahead and
          // create the new incoming value for this one.
          auto retyped_in_call = update_type(in_call, call->getType());
          new_phi->addIncoming(retyped_in_call, in_block);

          new_holes.insert(retyped_in_call);
        }

        replacements[user_phi] = new_phi;
      } else {
        invalid_state();
      }
    }
  }

  for (auto [st, ca] : replacements) {
    auto rec_holes = safe_rauw(st, ca);
    for (auto rh : rec_holes) {
      new_holes.insert(rh);
    }
  }

  if (stub->getParent()) {
    stub->eraseFromParent();
  }

  return new_holes;
}

CallInst* candidate::update_type(CallInst* stub, Type* new_rt)
{
  auto args_copy = std::vector<Value*> {};
  std::copy(stub->arg_begin(), stub->arg_end(), std::back_inserter(args_copy));

  auto ret = ctx().stub(new_rt, args_copy);
  ret->insertBefore(stub);
  return ret;
}

} // namespace presyn
