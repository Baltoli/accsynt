#include <props/props.h>
#include <support/thread_context.h>

using namespace support;
using namespace llvm;

namespace props {

Type *param::llvm_type() const
{
  auto base_type = [this] () -> Type* {
    switch(type) {
      case data_type::integer:
        return IntegerType::get(thread_context::get(), 32);
      case data_type::floating:
        return Type::getFloatTy(thread_context::get());
      default:
        assert(false && "Unsupported data type");
    }
  }();

  Type *full_type = base_type;
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

  return nullptr;
}

Function *signature::create_function(Module &mod) const
{
  return nullptr;
}

}
