#pragma once

#include <props/props.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

namespace presyn {

/**
 * Represents the abstract context that a fragment needs to know in order to
 * insert itself into a sketch. This is necessary in the first instance because
 * the types of parameters are not encoded in a fragment's template arguments
 * (i.e. @x could be typed as int* or double* in `fixed<@x, 2>`).
 *
 * Contexts are created by sketches on construction, and are queried by
 * fragments during their individual compilation processes.
 */
class sketch_context {
public:
  sketch_context(llvm::Module&, props::signature);

  llvm::Function* stub();
  llvm::Function* stub_for(llvm::Type*);

private:
  llvm::Module& module_;
  props::signature sig_;
};

} // namespace presyn
