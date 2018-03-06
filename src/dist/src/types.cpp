#include <dist/types.h>

#include <random>

using namespace llvm;

Integer::Integer(size_t b) :
  bits_(b)
{
  assert(b > 0 && "Integers must have at least one bit");
}

IntegerType *Integer::llvm_type() const
{
  return IntegerType::get(ThreadContext::get(), bits_);
}

Integer::example_t Integer::generate() const
{
  std::random_device rd;
  std::geometric_distribution<example_t> dis(0.1);
  return std::min(std::max(dis(rd), min()), max());
}

Integer::example_t Integer::max() const
{
  return (1 << (bits_ - 1)) - 1;
}

Integer::example_t Integer::min() const
{
  return -(1 << (bits_ - 1));
}
