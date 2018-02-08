#pragma once

#include <dist/function_callable.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <memory>
#include <random>
#include <type_traits>

namespace llvm {
  class Function;
  class Module;
}

namespace synth {

using create_t = std::function<llvm::Value *(llvm::IRBuilder<>&, llvm::Value *, llvm::Value *)>;

#define sizeof_array(x) (sizeof((x)) / sizeof((x)[0]))
#define FUNC(name) ([](auto& B, auto *v1, auto *v2) { return B.Create##name(v1, v2); })

static std::pair<create_t, int> linear_binary[] = {
  { FUNC(Add), 20 },
  { FUNC(Sub), 1 },
  { FUNC(Mul), 20 },
  /* { FUNC(UDiv), 1 }, */
  /* { FUNC(URem), 1 }, */
  /* { FUNC(SDiv), 1 }, */
  /* { FUNC(SRem), 1 }, */
  { FUNC(Shl), 1 },
  { FUNC(LShr), 1 },
  { FUNC(AShr), 1 },
  { FUNC(And), 1 },
  { FUNC(Or), 1 },
  { FUNC(Xor), 1 }
};

#undef FUNC

template <typename R, typename... Args>
class Linear {
public:
  Linear() :
    module_(std::make_unique<llvm::Module>("", C_)) {}

  void add_example(R ret, std::tuple<Args...> args);
  llvm::Function *operator()();

private:
  llvm::LLVMContext C_;
  std::unique_ptr<llvm::Module> module_;

  size_t value_count(llvm::Function *f) const;
  bool satisfies_examples(llvm::Function *f) const;
  llvm::Value *sample(llvm::Function *f) const;

  using example_t = std::pair<R, std::tuple<Args...>>;
  std::vector<example_t> examples_;
};

template <typename R, typename... Args>
void Linear<R, Args...>::add_example(R ret, std::tuple<Args...> args)
{
  examples_.push_back({ret, args});
}

template <typename R, typename... Args>
size_t Linear<R, Args...>::value_count(llvm::Function *f) const
{
  auto instrs = std::accumulate
    (std::begin(*f), std::end(*f), 0, [f](auto sum, auto& bb) {
      return sum + bb.size();
    });
  return instrs + f->arg_size();
}

template <typename R, typename... Args>
llvm::Value *Linear<R, Args...>::sample(llvm::Function *f) const
{
  auto range = value_count(f) - 1;

  auto gen = std::mt19937{std::random_device{}()};
  auto dist = std::uniform_int_distribution<decltype(range)>{0, range};

  auto index = dist(gen);

  if(index < f->arg_size()) {
    return f->arg_begin() + index;
  } else {
    auto count = f->arg_size();
    for(auto& BB : *f) {
      for(auto& I : BB) {
        if(count++ == index) {
          return &I;
        }
      }
    }
  }

  // Exceptional case here - correct way to handle it?
  return nullptr;
}

template <typename R, typename... Args>
llvm::Function *Linear<R, Args...>::operator()()
{
  auto ret_ty = get_llvm_type<R>(C_);
  auto arg_tys = std::array<llvm::Type*, sizeof...(Args)>{
    { get_llvm_type<Args>(C_)... }
  };

  auto fn_ty = llvm::FunctionType::get(ret_ty, arg_tys, false);
  auto B = llvm::IRBuilder<>{C_};

  auto weights = std::vector<int>{};
  std::transform(std::begin(linear_binary), std::end(linear_binary), std::back_inserter(weights),
      [](auto p) { return p.second; });

  auto gen = std::mt19937{std::random_device{}()};
  auto dist = std::discrete_distribution<>{std::begin(weights), std::end(weights)};

  while(true) {
    auto fn = llvm::Function::Create(fn_ty, llvm::GlobalValue::ExternalLinkage, "", module_.get());
    auto bb = llvm::BasicBlock::Create(C_, "", fn);
    B.SetInsertPoint(bb);

    for(auto i = 0; i < 10; ++i) {
      auto v1 = sample(fn);
      auto v2 = sample(fn);
      linear_binary[dist(gen)].first(B, v1, v2);
    }

    B.CreateRet(sample(fn));

    if(satisfies_examples(fn)) {
      return fn;
    } else {
      fn->eraseFromParent();
    }
  }
}

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<R>(f);
  return std::all_of(std::begin(examples_), std::end(examples_), [&fc](auto ex) {
    return fc(ex.second) == ex.first;
  });
}


}
