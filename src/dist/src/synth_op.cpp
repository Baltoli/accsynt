#include <dist/synth_op.h>

#include <llvm/IR/Value.h>

namespace {

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

}

bool Add::validate(value_array args)
{
  return validate_types(2, args);
}

bool Mul::validate(value_array args)
{
  return validate_types(2, args);
}
