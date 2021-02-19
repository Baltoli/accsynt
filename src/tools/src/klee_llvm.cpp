#include "klee_llvm.h"

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
{
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

    auto size_in_bytes
        = irb.CreateMul(size, ConstantInt::get(size->getType(), 8));

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
