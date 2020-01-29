#include "candidate.h"

#include <support/assert.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

using namespace llvm;

namespace {

bool is_digit(char c) { return std::isdigit(c); }

} // namespace

namespace presyn {

Value* candidate::create_operation(CallInst& ci)
{
  auto name = ci.getCalledFunction()->getName();
  if (!name.startswith("__")) {
    return nullptr;
  }

  auto build = IRBuilder(&ci);

  name = name.drop_front(2).take_until([](auto c) { return c == '.'; });
  auto name_prefix = ci.getName().take_until(is_digit);

  if (name == "load") {
    Value* ptr = ci.arg_begin()[0];
    Value* idx = ci.arg_begin()[1];

    auto gep = build.CreateGEP(ptr, idx, name_prefix + ".gep");
    auto load = build.CreateLoad(gep, name_prefix + ".load");
    return load;
  }

  if (name == "index") {
    // TODO: work out how to implement
    unimplemented();
  }

  if (name == "affine") {
    // TODO: work out how to implement
    unimplemented();
  }

  if (name == "eq") {
    unimplemented();
  }

  if (name == "inc") {
    unimplemented();
  }

  return nullptr;
}

} // namespace presyn
