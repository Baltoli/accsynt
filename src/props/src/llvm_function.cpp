#include <props/props.h>

using namespace llvm;

namespace props {

Type *param::llvm_type() const
{
  auto base_type = [this] {
    return nullptr;
  }();

  Type *full_type = base_type;
  for(auto i = 0; i < pointer_depth; ++i) {
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
