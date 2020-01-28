#pragma once

#include <llvm/IR/Module.h>

#include <memory>

namespace presyn {

class candidate {
public:
  candidate(std::unique_ptr<llvm::Module>&&);

  bool is_valid() const;

private:
  std::unique_ptr<llvm::Module> module_;
};

} // namespace presyn
