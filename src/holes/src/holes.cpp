#include <holes/holes.h>

#include <support/assert.h>
#include <support/containers.h>
#include <support/llvm_format.h>
#include <support/thread_context.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

using namespace llvm;

namespace holes {

provider::provider(LLVMContext& ctx, Module& mod)
    : ctx_(ctx)
    , mod_(mod)
    , hole_type_(StructType::create(ctx_, "hole"))
    , identities_ {}
    , holes_ {}
{
}

Module const& provider::module() const { return mod_; }

Module& provider::module() { return mod_; }

LLVMContext& provider::ctx() { return ctx_; }

Type* provider::hole_type() const { return hole_type_; }

std::unordered_set<llvm::Instruction*> const& provider::holes() const
{
  return holes_;
}

void provider::reset()
{
  ::support::erase_if(
      holes_, [this](auto h) { return h->getType() != hole_type(); });
}

void provider::rauw_nt(llvm::Instruction* before, llvm::Value* after)
{
  auto reps = std::unordered_map<Instruction*, Value*> {};

  rauw_nt_helper(before, after, reps);

  for (auto [old_i, new_i] : reps) {
    rauw_nt(old_i, new_i);
  }
}

void provider::rauw_nt_helper(
    llvm::Instruction* before, llvm::Value* after,
    std::unordered_map<Instruction*, Value*>& replacements)
{
  assertion(
      holes_.find(before) != holes_.end(),
      "RAUW-NT can only be used on values representing holes - use regular "
      "LLVM RAUW otherwise. Failed to replace {} with {}.",
      *before, *after);

  auto id_fn = get_identity(after->getType());
  auto after_id = CallInst::Create(id_fn, {after}, after->getName());

  // Handle the case where the 'after' is an unlinked instruction
  if (auto inst = dyn_cast<Instruction>(after); !inst->getParent()) {
    inst->insertBefore(before);
    after_id->insertAfter(inst);
  } else {
    after_id->insertBefore(before);
  }

  if (before->getType() == after_id->getType()) {
    before->replaceAllUsesWith(after_id);
  } else {
    // Different types so we need to recreate every stub call that *uses* the
    // result of this one separately.

    for (auto user : before->users()) {
      assertion(
          isa<CallInst>(user) || isa<PHINode>(user),
          "Users of stub calls must be calls or PHIs");

      if (auto user_call = dyn_cast<CallInst>(user)) {
        auto new_args = std::vector<Value*> {};
        for (auto& arg : user_call->args()) {
          new_args.push_back(arg == before ? after : arg);
        }

        auto new_call = IRBuilder(before).CreateCall(
            user_call->getCalledFunction(), new_args, before->getName());

        rauw_nt(user_call, new_call);
        replacements[user_call] = new_call;

      } else if (auto user_phi = dyn_cast<PHINode>(user)) {
        unimplemented();
      } else {
        invalid_state();
      }
    }
  }

  if (before->getParent()) {
    before->eraseFromParent();
  }

  holes_.erase(before);
  holes_.insert(after_id);
}

Instruction* provider::create_hole(Type* ty)
{
  auto ud_val = UndefValue::get(ty);
  auto id = get_identity(ty);
  return CallInst::Create(id, {ud_val}, "hole");
}

Instruction* provider::create_hole()
{
  auto new_hole = create_hole(hole_type());
  holes_.insert(new_hole);
  return new_hole;
}

void provider::add_hole(Instruction* inst) { holes_.insert(inst); }

Function* provider::get_identity(Type* ty)
{
  if (identities_.find(ty) == identities_.end()) {
    auto ft = FunctionType::get(ty, {ty}, false);
    auto func = Function::Create(ft, GlobalValue::InternalLinkage, "id", &mod_);
    auto arg = func->getArg(0);
    auto bb = BasicBlock::Create(ctx_, "entry", func);
    ReturnInst::Create(ctx_, arg, bb);

    identities_[ty] = func;
  }

  return identities_.at(ty);
}

} // namespace holes
