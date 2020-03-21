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

  std::transform(
      parameters.begin(), parameters.end(), std::back_inserter(param_types),
      [](auto p) { return p.llvm_type(); });

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

std::optional<data_type> data_type::from_llvm(llvm::Type* ty)
{
  if (ty->isFloatTy()) {
    return data_type {base_type::floating, 0};
  } else if (ty->isIntegerTy(1)) {
    return data_type {base_type::boolean, 0};
  } else if (ty->isIntegerTy(8)) {
    return data_type {base_type::character, 0};
  } else if (ty->isIntegerTy(32)) {
    return data_type {base_type::integer, 0};
  } else if (ty->isPointerTy()) {
    auto depth = 1u;
    auto ptr_ty = dyn_cast<PointerType>(ty);
    auto elt_ty = ptr_ty->getElementType();

    while (elt_ty->isPointerTy()) {
      ++depth;
      elt_ty = dyn_cast<PointerType>(elt_ty)->getElementType();
    }

    if (auto maybe_elt = data_type::from_llvm(elt_ty)) {
      return data_type {maybe_elt->base, depth};
    }
  }

  return std::nullopt;
}

signature signature::from_llvm(FunctionType* ty) { return {}; }

} // namespace props
