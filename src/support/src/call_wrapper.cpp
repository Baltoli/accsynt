#include <support/call_wrapper.h>
#include <support/llvm_cloning.h>
#include <support/thread_context.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

using namespace props;
using namespace support;

using namespace llvm;

namespace support {

namespace {

signature get_sig(Module const& mod, std::string const& name)
{
  auto func = mod.getFunction(name);
  if (!func) {
    throw std::runtime_error("No such function");
  }

  auto sig = signature::from_llvm(func->getFunctionType(), name);
  if (!sig) {
    throw std::runtime_error("Invalid LLVM type signature for JIT call");
  }

  return *sig;
}

} // namespace

call_wrapper::call_wrapper(
    signature sig, llvm::Module const& mod, std::string const& name)
    : signature_(sig)
{
  auto mod_copy = copy_module_to(thread_context::get(), mod);

  impl_ = mod_copy->getFunction(name);
  if (!impl_) {
    impl_ = sig.create_function(*mod_copy);
  }

  wrapper_ = build_wrapper_function(*mod_copy, impl_);

  auto topts = TargetOptions {};
  std::string err;

  verifyModule(*mod_copy, &llvm::errs());

  auto eb = llvm::EngineBuilder {std::move(mod_copy)};
  eb.setErrorStr(&err);
  eb.setEngineKind(EngineKind::JIT);
  eb.setTargetOptions(topts);
  engine_.reset(eb.create());

  if (!engine_) {
    throw std::runtime_error("Engine creation failed: " + err);
  }
}

call_wrapper::call_wrapper(Module const& mod, std::string const& name)
    : call_wrapper(get_sig(mod, name), mod, name)
{
}

call_wrapper::call_wrapper(Function const& func)
    : call_wrapper(*func.getParent(), func.getName())
{
}

call_wrapper::call_wrapper(
    signature sig, llvm::Module const& mod, std::string const& name,
    dynamic_library const& dl)
    : call_wrapper(sig, mod, name)
{
  auto sym = dl.raw_symbol(name);
  engine_->addGlobalMapping(impl_, sym);
}

call_builder call_wrapper::get_builder() const
{
  return call_builder(signature_);
}

uint64_t call_wrapper::call(call_builder& build)
{
  auto addr = engine_->getPointerToFunction(wrapper_);
  engine_->finalizeObject();
  auto jit_fn = reinterpret_cast<uint64_t (*)(uint8_t*)>(addr);
  auto args = build.args();
  return jit_fn(args);
}

size_t call_wrapper::marshalled_size(llvm::Type const* type) const
{
  if (type->isIntegerTy(32) || type->isFloatTy()) {
    return 4;
  } else if (type->isPointerTy()) {
    return 8;
  } else {
    return 0;
  }
}

Function* call_wrapper::build_wrapper_function(Module& mod, Function* fn) const
{
  auto& ctx = thread_context::get();

  auto name = fn->getName().str() + "_wrap";
  auto rt = IntegerType::get(ctx, 64);
  auto byte_t = IntegerType::get(ctx, 8);
  auto ptr_t = byte_t->getPointerTo();
  auto fn_ty = FunctionType::get(rt, {ptr_t}, false);

  auto new_fn
      = Function::Create(fn_ty, GlobalValue::ExternalLinkage, name, &mod);
  auto bb = BasicBlock::Create(ctx, "entry", new_fn);
  auto B = IRBuilder<>(bb);

  size_t offset = 0;
  auto arg_data = new_fn->arg_begin();

  auto call_args = std::vector<Value*> {};

  for (auto it = fn->arg_begin(); it != fn->arg_end(); ++it) {
    auto arg_type = it->getType();

    auto size = marshalled_size(arg_type);
    auto vec = make_vector(B, size);

    for (auto i = 0u; i < size; ++i) {
      auto gep = B.CreateGEP(arg_data, B.getInt64(offset));
      auto val = B.CreateLoad(gep);
      vec = B.CreateInsertElement(vec, val, i);
      ++offset;
    }

    if (arg_type->isPointerTy()) {
      auto cast = B.CreateBitCast(vec, IntegerType::get(ctx, 64));
      auto ptr = B.CreateIntToPtr(cast, arg_type);
      call_args.push_back(ptr);
    } else {
      auto cast = B.CreateBitCast(vec, it->getType());
      call_args.push_back(cast);
    }
  }

  auto call = B.CreateCall(fn, call_args);
  if (signature_.return_type) {
    make_return(B, call);
  } else {
    make_return(B);
  }

  return new_fn;
}

std::string call_wrapper::name() const { return implementation()->getName(); }

} // namespace support
