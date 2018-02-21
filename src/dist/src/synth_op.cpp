#include <dist/synth_op.h>

using namespace llvm;

bool validate_types(size_t num, value_array args)
{
  if(num == 0) { return true; }

  auto begin = std::begin(args);
  auto end = std::begin(args) + num;

  return std::size(args) >= num &&
         std::all_of(begin, end, [] (auto v) { return v; }) &&
         std::all_of(begin, end, [&args] (auto v) {
            return v->getType() == args[0]->getType();
         });
}

size_t max_gep_depth(Type *t)
{
  if(auto ptr = dyn_cast<PointerType>(t)) {
    return 1 + max_gep_depth(ptr->getElementType());
  } else if(auto arr =  dyn_cast<ArrayType>(t)) {
    return 1 + max_gep_depth(arr->getElementType());
  } else {
    // TODO: handle structs
    return 0;
  }
}

Ops& Ops::instance()
{
  static auto inst = Ops{};
  return inst;
}
