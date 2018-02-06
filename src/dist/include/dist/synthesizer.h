#pragma once

#include <dist/function_callable.h>
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

  bool satisfies_examples(llvm::Function *f);

  using example_t = std::pair<R, std::tuple<Args...>>;
  std::vector<example_t> examples;
};

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f)
{
  auto fc = FunctionCallable<R>(f);
  for(auto ex : examples) {
    
  }
}


}
