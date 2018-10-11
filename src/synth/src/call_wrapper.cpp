#include "call_wrapper.h"

#include <support/llvm_cloning.h>
#include <support/thread_context.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

using namespace props;
using namespace support;

using namespace llvm;

namespace synth {

call_wrapper::call_wrapper(signature sig, 
                           llvm::Module const& mod, 
                           std::string const& name)
  :builder_(sig)
{
  auto mod_copy = copy_module_to(thread_context::get(), mod);

  impl_ = sig.create_function(*mod_copy);
  wrapper_ = build_wrapper_function(*mod_copy, impl_);

  auto topts = TargetOptions{};
  std::string err;

  mod_copy->print(llvm::errs(), nullptr);
  verifyModule(*mod_copy, &llvm::errs());

  auto eb = llvm::EngineBuilder{std::move(mod_copy)};
  eb.setErrorStr(&err);
  eb.setEngineKind(EngineKind::JIT);
  eb.setTargetOptions(topts);
  engine_.reset(eb.create());

  if(!engine_) {
    errs() << "BAD: engine not created\n";
    errs() << err << '\n';
    throw std::runtime_error("Engine creation failed");
  }
}

call_wrapper::call_wrapper(signature sig, 
                           llvm::Module const& mod, 
                           std::string const& name, 
                           dynamic_library const& dl)
  : call_wrapper(sig, mod, name)
{
  auto sym = dl.raw_symbol(name);
  engine_->addGlobalMapping(impl_, sym);
}

void call_wrapper::call()
{
  call(builder_);
}

void call_wrapper::call(call_builder build)
{
  auto addr = engine_->getPointerToFunction(wrapper_);
  engine_->finalizeObject();
  auto jit_fn = reinterpret_cast<int (*)(uint8_t *)>(addr);
  auto args = build.args();
  errs() << jit_fn(args) << '\n';
}

size_t call_wrapper::marshalled_size(llvm::Type const* type) const
{
  if(type->isIntegerTy(32)) {
    return 4;
  } else if(type->isFloatTy()) {
    return 4;
  } else if(type->isPointerTy()) {
    return 8;
  } else {
    return 0;
  }
}

Function *call_wrapper::build_wrapper_function(Module& mod, Function *fn) const
{
  auto& ctx = thread_context::get();

  auto name = fn->getName().str() + "_wrap";
  auto rt = fn->getFunctionType()->getReturnType();
  auto byte_t = IntegerType::get(ctx, 8);
  auto ptr_t = byte_t->getPointerTo();
  auto fn_ty = FunctionType::get(rt, {ptr_t}, false);

  auto new_fn = Function::Create(fn_ty, GlobalValue::ExternalLinkage, name, &mod);
  auto bb = BasicBlock::Create(ctx, "entry", new_fn);
  auto B = IRBuilder<>(bb);

  size_t offset = 0;
  auto arg_data = new_fn->arg_begin();

  auto call_args = std::vector<Value *>{};

  for(auto it = fn->arg_begin(); it != fn->arg_end(); ++it) {
    auto size = marshalled_size(it->getType());
    auto vec = make_vector(B, size);

    for(auto i = 0u; i < size; ++i) {
      auto gep = B.CreateGEP(arg_data, { B.getInt64(offset) });
      auto val = B.CreateLoad(gep);
      vec = B.CreateInsertElement(vec, val, i);
      ++offset;
    }

    auto cast = B.CreateBitCast(vec, it->getType());
    call_args.push_back(cast);
  }

  auto call = B.CreateCall(fn, call_args);
  B.CreateRet(call);
  return new_fn;
}

}
