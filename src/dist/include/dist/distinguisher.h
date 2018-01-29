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

class Distinguisher {
public:
  Distinguisher(
    llvm::Function *f,
    llvm::Function *g,
    std::string id=""
  );

  std::optional<std::vector<llvm::GenericValue>> operator()() const;
private:
  static llvm::Function *function_interface_copy(llvm::Function *f, llvm::Module *m);

  size_t arg_size() const;

  template<class... Args>
  auto get_arg_values(Args... args) const;

  template<class... Args>
  uint64_t run_f(Args... args) const;

  template<class... Args>
  uint64_t run_g(Args... args) const;

  llvm::GenericValue run_function(llvm::Function *f, 
                                  llvm::ArrayRef<llvm::GenericValue> args) const;

  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;
  llvm::Function *f_;
  llvm::Function *g_;
};

template<class... Args>
auto Distinguisher::get_arg_values(Args... args) const
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
uint64_t Distinguisher::run_f(Args... args) const
{
  return run_function(f_, get_arg_values(args...)).IntVal.getLimitedValue();
}

template<class... Args>
uint64_t Distinguisher::run_g(Args... args) const
{
  return run_function(g_, get_arg_values(args...)).IntVal.getLimitedValue();
}
