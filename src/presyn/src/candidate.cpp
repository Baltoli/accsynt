#include "candidate.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>

#include <algorithm>

using namespace llvm;

namespace presyn {

candidate::candidate(std::unique_ptr<Module>&& mod)
    : module_(std::move(mod))
{
}

bool candidate::is_valid() const
{
  return std::any_of(module_->begin(), module_->end(), [](auto const& func) {
    // TODO: Get the real function name from a props::signature?
    //       At the moment, this is checking that there is at least one function
    //       in the module that isn't a declaration, and that *does not call*
    //       any declarations in its body. When the signature name is inlined,
    //       we can check only the relevant function.
    if (func.isDeclaration()) {
      return false;
    }

    // For the function to be valid, all of its basic blocks must contain no
    // instructions that are call instructions to functions without definitions.
    return std::all_of(func.begin(), func.end(), [](auto const& bb) {
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
  });
}

} // namespace presyn
