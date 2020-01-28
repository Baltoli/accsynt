#pragma once

#include <props/props.h>

#include <llvm/IR/Module.h>

#include <memory>

namespace presyn {

class candidate {
public:
  candidate(props::signature, std::unique_ptr<llvm::Module>&&);

  bool is_valid() const;

  llvm::Function* function() const;

private:
  props::signature signature_;
  std::unique_ptr<llvm::Module> module_;
};

} // namespace presyn
