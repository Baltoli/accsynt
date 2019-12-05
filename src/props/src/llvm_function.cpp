#include <props/props.h>
#include <support/thread_context.h>

using namespace support;
using namespace llvm;

namespace props {

Type* base_llvm_type(base_type dt)
{
  switch (dt) {
  case base_type::character:
    return IntegerType::get(thread_context::get(), 8);
  case base_type::boolean:
    return IntegerType::get(thread_context::get(), 1);
  case base_type::integer:
    return IntegerType::get(thread_context::get(), 32);
  case base_type::floating:
    return Type::getFloatTy(thread_context::get());
  default:
    assert(false && "Unsupported data type");
  }

  __builtin_unreachable();
}

Type* base_llvm_return_type(std::optional<data_type> dt)
{
  if (dt) {
    auto base_ty = base_llvm_type(dt->base);
    for (auto i = 0u; i < dt->pointers; ++i) {
      base_ty = PointerType::getUnqual(base_ty);
    }
    return base_ty;
  } else {
    return Type::getVoidTy(thread_context::get());
  }
}

Type* param::llvm_type() const
{
  Type* full_type = base_llvm_type(type);

  for (auto i = 0; i < pointer_depth; ++i) {
    full_type = PointerType::getUnqual(full_type);
  }

  return full_type;
}

FunctionType* signature::function_type() const
{
  auto param_types = std::vector<Type*> {};

  std::transform(parameters.begin(), parameters.end(),
      std::back_inserter(param_types), [](auto p) { return p.llvm_type(); });

  return FunctionType::get(
      base_llvm_return_type(return_type), param_types, false);
}

Function* signature::create_function(Module& mod) const
{
  auto full_name = name;
  auto fn_const
      = mod.getOrInsertFunction(full_name, function_type()).getCallee();
  if (!isa<Function>(fn_const)) {
    throw std::runtime_error("Bad: const not function");
  }
  auto fn = dyn_cast<Function>(fn_const);

  auto i = 0;
  for (auto it = fn->arg_begin(); it != fn->arg_end(); ++it, ++i) {
    it->setName(parameters.at(i).name);
  }

  return fn;
}
} // namespace props
