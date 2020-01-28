#pragma once

#include <props/props.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include <map>
#include <string>
#include <vector>

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

  props::signature signature() const { return sig_; }

  /**
   * Creating a stub function essentially says "give me some value at synthesis
   * time, the type of which I may not know already".
   *
   * A later phase (refinement / synthesis) will work out sensible concrete
   * types for these stubs, then use them to synthesise actual programs by
   * assigning actual values to the points where the stub exists.
   */
  llvm::CallInst* stub();
  llvm::CallInst* stub(llvm::Type*);

  llvm::CallInst* stub(std::vector<llvm::Value*> const&);
  llvm::CallInst* stub(llvm::Type*, std::vector<llvm::Value*> const&);

  llvm::CallInst* stub(std::string const&);
  llvm::CallInst* stub(llvm::Type*, std::string const&);

  /**
   * Creates an operation with the specified name - the exact semantics of the
   * operation will be left up to the refinement phase of synthesis (i.e. they
   * are just placeholders at this point).
   *
   * However, by attaching some standard meaning to them, we can simulate the
   * parts of fragment compilation with known semantics ahead of time by giving
   * them specified names (on functions that operate on particular types). These
   * can then be "stamped out" by the refinement step at the time of actual
   * synthesis.
   *
   * Each operation function will end up (much like stubs) being variadic, such
   * that the correct implementations can be unified and stamped out at
   * compilation.
   */
  llvm::CallInst*
  operation(std::string const&, llvm::Type*, std::vector<llvm::Value*> const&);

  llvm::CallInst*
  operation(std::string const&, std::vector<llvm::Value*> const&);

private:
  llvm::Constant* constant_name(std::string const&);

  llvm::Module& module_;
  props::signature sig_;
  llvm::Type* opaque_type_;

  std::map<llvm::Type*, llvm::Function*> stubs_;
  std::map<std::string, llvm::Constant*> names_;
  std::map<std::pair<std::string, llvm::Type*>, llvm::Function*> ops_;
};

} // namespace presyn
