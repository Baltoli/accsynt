#include <props/props.h>
#include <support/thread_context.h>

using namespace support;
using namespace llvm;

namespace props {

Type *base_llvm_type(data_type dt)
{
  switch(dt) {
    case data_type::integer:
      return IntegerType::get(thread_context::get(), 32);
    case data_type::floating:
      return Type::getFloatTy(thread_context::get());
    default:
      assert(false && "Unsupported data type");
  }
}

Type *base_llvm_return_type(std::optional<data_type> dt)
{
  if(dt) {
    return base_llvm_type(dt.value());
  } else {
    return Type::getVoidTy(thread_context::get());
  }
}

Type *param::llvm_type() const
{
  Type *full_type = base_llvm_type(type);

  for(auto i = 0; i < pointer_depth; ++i) {
    full_type = PointerType::getUnqual(full_type);
  }

  return full_type;
}

FunctionType *signature::function_type() const
{
  auto param_types = std::vector<Type *>{};

  std::transform(parameters.begin(), parameters.end(), 
                 std::back_inserter(param_types), 
                 [](auto p) { return p.llvm_type(); });

  return FunctionType::get(base_llvm_return_type(return_type), 
                           param_types, false);
}

Function *signature::create_function(Module &mod) const
{
  auto full_name = name;
  auto fn =  Function::Create(function_type(), Function::ExternalLinkage, 
                              full_name, &mod);

  auto i = 0;
  for(auto it = fn->arg_begin();
      it != fn->arg_end(); ++it, ++i) {
    it->setName(parameters.at(i).name);
  }

  return fn;
}

}
