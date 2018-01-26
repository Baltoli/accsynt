#pragma once

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/LLVMContext.h>

#include <array>
#include <string>

namespace llvm {
  class Function;
  class LLVMContext;
  class Module;
}

class Distinguisher {
public:
  Distinguisher(
    llvm::Function *f,
    llvm::Function *g,
    std::string id=""
  );

  template<class... Args>
  llvm::GenericValue run_f(Args... args);

  template<class... Args>
  llvm::GenericValue run_g(Args... args);

private:
  template<class... Args>
  auto get_arg_values(Args... args);

  llvm::GenericValue run_function(llvm::Function *f, 
                                  llvm::ArrayRef<llvm::GenericValue> args);

  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;
  llvm::Function *f_;
  llvm::Function *g_;
};

template<class... Args>
auto Distinguisher::get_arg_values(Args... args)
{
  constexpr auto make_generic_int = [](const auto i) {
    llvm::GenericValue gv;
    gv.IntVal = llvm::APInt(sizeof(i)*8, i, std::is_signed_v<decltype(i)>);
    return gv;
  };

  return std::array<llvm::GenericValue, sizeof...(Args)>{
    { make_generic_int(args)... }
  };
}

template<class... Args>
llvm::GenericValue Distinguisher::run_f(Args... args)
{
  return run_function(f_, get_arg_values(args...));
}

template<class... Args>
llvm::GenericValue Distinguisher::run_g(Args... args)
{
  return run_function(g_, get_arg_values(args...));
}
