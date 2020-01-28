#include "candidate.h"

#include <support/assert.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <algorithm>

using namespace llvm;

namespace presyn {

candidate::candidate(props::signature sig, std::unique_ptr<Module>&& mod)
    : signature_(sig)
    , module_(std::move(mod))
{
}

Function* candidate::function() const
{
  return module_->getFunction(signature_.name);
}

bool candidate::is_valid() const
{
  auto func = function();

  if (func) {
    // For the function to be valid, all of its basic blocks must contain no
    // instructions that are call instructions to functions without definitions.
    return std::all_of(func->begin(), func->end(), [](auto const& bb) {
      return std::none_of(bb.begin(), bb.end(), [](auto const& inst) {
        if (auto ci = dyn_cast<CallInst>(&inst)) {
          auto fn = ci->getCalledFunction();
          if (fn->isDeclaration()) {
            return true;
          }
        }

        return false;
      });
    });
  }

  return false;
}

} // namespace presyn
