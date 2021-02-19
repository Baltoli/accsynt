#include "klee_llvm.h"

#include <support/assert.h>
#include <support/llvm_format.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/CommandLine.h>

using namespace llvm;
using namespace props;

static cl::opt<int> SymbolicArraySize(
    "sym-size", cl::desc("Number of symbolic entries to allocate per array"),
    cl::desc("integer"), cl::init(8));

klee_decls::klee_decls(Module& mod)
    : make_symbolic(create_klee_make_symbolic(mod))
    , assume(create_assume(mod))
    , assert_(create_assert(mod))
    , main_(create_main(mod))
    , array_size(create_array_size(mod))
    , array_equals_ {}
{
}

Value* klee_decls::check_all_equal(
    IRBuilder<>& irb, Value* size, std::vector<Value*> const& ref,
    std::vector<Value*> const& other)
{
  assertion(
      ref.size() == other.size(),
      "Comparing differently sized argument sets ({} : {})", ref.size(),
      other.size());

  Value* running = irb.getTrue();

  for (auto i = 0u; i < ref.size(); ++i) {
    auto ref_ty = ref[i]->getType();
    auto other_ty = other[i]->getType();

    assertion(
        ref_ty == other_ty,
        "Comparing differently typed argument sets: ({} : {})", *ref_ty,
        *other_ty);

    if (auto ptr_ty = dyn_cast<PointerType>(ref_ty)) {
      auto size = irb.CreateCall(array_size);
      if (array_equals_.find(ptr_ty) == array_equals_.end()) {
        auto size_ty = size->getType();

        auto fn_ty = FunctionType::get(
            irb.getInt1Ty(), {size_ty, ptr_ty, ptr_ty}, false);

        auto fn = Function::Create(
            fn_ty, GlobalValue::InternalLinkage, "array_eq",
            irb.GetInsertBlock()->getParent()->getParent());

        auto entry = BasicBlock::Create(fn->getContext(), "entry", fn);
        auto header = BasicBlock::Create(fn->getContext(), "header", fn);
        auto body = BasicBlock::Create(fn->getContext(), "body", fn);
        auto exit = BasicBlock::Create(fn->getContext(), "exit", fn);

        auto in_b = IRBuilder<>(entry);
        in_b.CreateBr(header);

        in_b.SetInsertPoint(header);
        auto iter = in_b.CreatePHI(size_ty, 2);
        iter->addIncoming(ConstantInt::get(size_ty, 0), entry);
        auto all = in_b.CreatePHI(in_b.getInt1Ty(), 2);
        all->addIncoming(in_b.getTrue(), entry);
        auto cond = in_b.CreateICmpSLT(iter, fn->getArg(0));
        in_b.CreateCondBr(cond, body, exit);

        in_b.SetInsertPoint(body);
        auto ref_idx = in_b.CreateGEP(fn->getArg(1), iter);
        auto other_idx = in_b.CreateGEP(fn->getArg(2), iter);
        auto ref_load = in_b.CreateLoad(ref_idx);
        auto other_load = in_b.CreateLoad(other_idx);
        auto eq = create_eq(in_b, ref_load, other_load);
        auto next_all = in_b.CreateAnd(all, eq);
        all->addIncoming(next_all, body);
        auto next_iter
            = in_b.CreateAdd(iter, ConstantInt::get(iter->getType(), 1));
        iter->addIncoming(next_iter, body);
        in_b.CreateBr(header);

        in_b.SetInsertPoint(exit);
        in_b.CreateRet(all);

        array_equals_[ptr_ty] = fn;
      }

      running = irb.CreateAnd(
          running,
          irb.CreateCall(array_equals_.at(ref_ty), {size, ref[i], other[i]}));
    }
  }

  return running;
}

std::vector<Value*>
klee_decls::allocate_symbolic(IRBuilder<>& irb, signature const& sig)
{
  auto ret = std::vector<Value*> {};
  auto array_size_v = irb.CreateCall(array_size);

  for (auto const& param : sig.parameters) {
    auto base_ty = base_llvm_type(param.type);

    auto size = [&]() -> Value* {
      if (param.pointer_depth == 0) {
        return ConstantInt::get(get_size_ty(irb.getContext()), 1);
      } else {
        return array_size_v;
      }
    }();

    auto alloc = irb.CreateAlloca(base_ty, size, param.name);
    auto cast_alloc
        = irb.CreatePointerCast(alloc, irb.getInt8Ty()->getPointerTo());

    auto pointed = cast<PointerType>(alloc->getType())->getElementType();
    auto size_in_bytes = irb.CreateMul(
        size,
        ConstantInt::get(size->getType(), pointed->getScalarSizeInBits() / 8));

    irb.CreateCall(
        make_symbolic,
        {cast_alloc, size_in_bytes, irb.CreateGlobalStringPtr(param.name)});

    if (param.pointer_depth == 0) {
      ret.push_back(irb.CreateLoad(alloc));
    } else {
      ret.push_back(alloc);
    }
  }

  return ret;
}

Function* klee_decls::create_array_size(Module& mod)
{
  auto& ctx = mod.getContext();

  auto size_ty = get_size_ty(ctx);

  auto fn_ty = FunctionType::get(size_ty, {}, false);

  auto func = Function::Create(
      fn_ty, GlobalValue::InternalLinkage, "array_size", &mod);

  auto entry = BasicBlock::Create(ctx, "entry", func);

  auto irb = IRBuilder<>(entry);
  irb.CreateRet(ConstantInt::get(size_ty, SymbolicArraySize));

  return func;
}

Function* klee_decls::create_klee_make_symbolic(Module& mod)
{
  auto& ctx = mod.getContext();

  auto vp_ty = IntegerType::get(ctx, 8)->getPointerTo();
  auto size_ty = get_size_ty(ctx);
  auto void_ty = Type::getVoidTy(ctx);

  auto fn_ty = FunctionType::get(void_ty, {vp_ty, size_ty, vp_ty}, false);

  auto func = Function::Create(
      fn_ty, GlobalValue::ExternalLinkage, "klee_make_symbolic", &mod);

  return func;
}

Function* klee_decls::create_assume(Module& mod)
{
  auto& ctx = mod.getContext();

  auto void_ty = Type::getVoidTy(ctx);
  auto bool_ty = IntegerType::get(ctx, 1);

  auto fn_ty = FunctionType::get(void_ty, {bool_ty}, false);

  auto func = Function::Create(
      fn_ty, GlobalValue::ExternalLinkage, "klee_assume", &mod);

  return func;
}

Function* klee_decls::create_assert(Module& mod)
{
  auto& ctx = mod.getContext();

  auto void_ty = Type::getVoidTy(ctx);
  auto bool_ty = IntegerType::get(ctx, 1);

  auto fn_ty = FunctionType::get(void_ty, {bool_ty}, false);

  auto func
      = Function::Create(fn_ty, GlobalValue::ExternalLinkage, "assert", &mod);

  return func;
}

Function* klee_decls::create_main(Module& mod)
{
  auto& ctx = mod.getContext();

  auto i32_ty = IntegerType::get(ctx, 32);
  auto char_ty = IntegerType::get(ctx, 8);
  auto argv_ty = char_ty->getPointerTo()->getPointerTo();

  auto fn_ty = FunctionType::get(i32_ty, {i32_ty, argv_ty}, false);

  auto func
      = Function::Create(fn_ty, GlobalValue::ExternalLinkage, "main", &mod);

  return func;
}

Type* get_size_ty(LLVMContext& ctx)
{
  return IntegerType::get(ctx, sizeof(size_t) * 8);
}

Value* create_eq(IRBuilder<>& irb, Value* a, Value* b)
{
  if (a->getType()->isIntegerTy()) {
    return irb.CreateICmpEQ(a, b);
  } else if (a->getType()->isFloatingPointTy()) {
    return irb.CreateFCmpUEQ(a, b);
  } else {
    invalid_state();
  }
}
