#pragma once

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

struct Count : public llvm::FunctionPass {
  static char ID;

  Count();

  bool runOnFunction(llvm::Function& F) override;

  int getCount() const;

private:
  int count_;
};
