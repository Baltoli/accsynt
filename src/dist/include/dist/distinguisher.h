#pragma once

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/LLVMContext.h>

#include <array>
#include <string>
#include <optional>
#include <vector>

namespace llvm {
  class Function;
  class LLVMContext;
  class Module;
}

/**
 * A FunctionDistinguisher is responsible for discovering input arguments to a pair of
 * LLVM functions such that the functions' behaviour differs at those inputs
 * (i.e. it implements a distinguishing input oracle for the two functions).
 * Once constructed, the distinguisher can be called to generate such an input
 * (if one exists / can be found).
 */
class FunctionDistinguisher {
public:
  /**
   * The FunctionDistinguisher object does not take ownership of the two functions f and
   * g it is passed at construction time. Instead, it copies them both into a
   * new internal module. The module ID can be specified using this constructor,
   * as can the number of possible inputs to try before deciding the two
   * functions are identical.
   */
  FunctionDistinguisher(
    llvm::Function *f,
    llvm::Function *g,
    std::string id="",
    size_t limit=10000
  );

  /**
   * Returns an optional vector of LLVM values that are a distinguishing input
   * for the two functions (i.e. their behaviour differs for that input).
   */
  std::optional<std::vector<llvm::GenericValue>> operator()() const;

private:
  /**
   * Get the number of arguments expected by the two functions managed by this
   * distinguisher.
   */
  size_t arg_size() const;

  /**
   * Run an LLVM function on the supplied arguments using the LLVM interpreter.
   */
  llvm::GenericValue run_function(llvm::Function *f, 
                                  llvm::ArrayRef<llvm::GenericValue> args) const;

  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;
  llvm::Function *f_;
  llvm::Function *g_;
  size_t example_limit_;
};
