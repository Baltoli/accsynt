#pragma once

#include <dist/utils.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include <memory>

namespace llvm {
  class Function;
  class Module;
}

namespace synth {

using create_t = std::function<llvm::Value *(llvm::IRBuilder<>&, llvm::Value *, llvm::Value *)>;

#define FUNC(name) ([](auto& B, auto *v1, auto *v2) { return B.Create##name(v1, v2); })

static create_t linear_binary[] = {
  FUNC(Add),
  FUNC(Sub),
  FUNC(Mul),
  FUNC(UDiv),
  FUNC(URem),
  FUNC(SDiv),
  FUNC(SRem),
  FUNC(Shl),
  FUNC(LShr),
  FUNC(AShr),
  FUNC(And),
  FUNC(Or),
  FUNC(Xor),
};

#undef FUNC

template <typename R, typename... Args>
class Linear {
public:
  Linear() :
    module_(std::make_unique<llvm::Module>("", C_)) {}

private:
  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;
};

}
