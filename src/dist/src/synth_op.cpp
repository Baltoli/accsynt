#include <dist/synth_op.h>

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

Ops& Ops::instance()
{
  static auto inst = Ops{};
  return inst;
}
