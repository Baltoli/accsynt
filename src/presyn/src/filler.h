#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

namespace presyn {

class candidate;

/**
 * Interface that represents something capable of choosing values for a
 * particular hole. The only operation publicly visible is construction;
 * everything else is handled by passing it to a newly constructed candidate.
 */
class filler {
  friend class candidate;

public:
  virtual ~filler() = default;

  llvm::Value* copy_value(llvm::Value*) const;

  bool has_unknown_type(llvm::Value*) const;
  bool has_known_type(llvm::Value*) const;
  bool is_hole(llvm::Value*) const;
  bool is_value(llvm::Value*) const;

  llvm::CallInst* select_type(llvm::CallInst*, llvm::Type*);

protected:
  void set_candidate(candidate&);
  candidate& get_candidate() const;

  virtual llvm::Value* fill(llvm::CallInst*) = 0;

private:
  candidate* candidate_ = nullptr;
};

/**
 * Intentionally stupid filler implementation to test the interface - it always
 * fills holes with the constant value 0 for the same type as the hole.
 */
class zero_filler : public filler {
public:
  zero_filler() = default;

protected:
  llvm::Value* fill(llvm::CallInst*) override;
};

} // namespace presyn
