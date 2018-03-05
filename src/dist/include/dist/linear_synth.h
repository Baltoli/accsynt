#pragma once

#include <dist/function_callable.h>
#include <dist/synth_op.h>
#include <dist/types.h>
#include <dist/utils.h>

#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <algorithm>
#include <forward_list>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <type_traits>

namespace llvm {
  class Function;
  class Module;
}

namespace synth {

template <typename R, typename... Args>
class Linear {
public:
  using ret_t = typename R::example_t;
  using args_t = std::tuple<typename Args::example_t...>;
  using io_pair_t = std::pair<ret_t, args_t>;

  Linear(R r, Args... args) :
    return_type_{r}, arg_types_{args...},
    examples_{}
  {}

  void add_example(ret_t ret, args_t args);
  std::unique_ptr<llvm::Module> operator()();

  std::tuple<Args...> arg_types() const { return arg_types_; }

private:
  llvm::FunctionType *llvm_function_type() const;
  bool satisfies_examples(llvm::Function *f) const;

  void clear_functions(llvm::Module& module);

  template <typename Builder>
  void populate_instructions(Builder&& b, ValueSampler& sampler, 
                             llvm::Function *fn, size_t n) const;

  template <typename Builder>
  llvm::Value *create_return(Builder&& b, ValueSampler& sampler,
                             llvm::Function *fn) const;

  template <typename Builder>
  void create_oob_returns(Builder&& b, ValueSampler& sampler,
                          llvm::Function *fn) const;

  std::unique_ptr<llvm::Module> generate_candidate(bool&);

  R return_type_;
  std::tuple<Args...> arg_types_;

  std::vector<io_pair_t> examples_;
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::operator()()
{
  auto ret = std::unique_ptr<llvm::Module>{};
  bool done = false;

  auto work = [&] {
    auto cand = generate_candidate(done);
    if(cand) {
      ret = std::move(cand);
    }
  };

  auto threads = std::forward_list<std::thread>{};
  auto max_threads = 1;//std::max(1u, std::thread::hardware_concurrency() - 1);
  for(auto i = 0; i < max_threads; ++i) {
    threads.emplace_front(work);
  }

  for(auto& t : threads) {
    t.join();
  }

  return ret;
}

template <typename R, typename... Args>
template <typename Builder>
void Linear<R, Args...>::populate_instructions(Builder&& B,
                                               ValueSampler& sampler, 
                                               llvm::Function *fn, 
                                               size_t n) const
{
  auto& meta = sampler.metadata();

  for(auto arg = std::next(fn->arg_begin()); arg != fn->arg_end(); ++arg) {
    meta.make_live(arg);
  }

  for(auto i = 0u; i < n; ++i) {
    auto v1 = util::uniform_sample(meta.live_set());
    auto v2 = util::uniform_sample(meta.live_set());
    
    if(auto next = sampler(B, {v1, v2})) {
      meta.make_live(next);
    }
  }
}

template <typename R, typename... Args>
template <typename Builder>
llvm::Value *Linear<R, Args...>::create_return(Builder&& B, 
                                               ValueSampler& sampler,
                                               llvm::Function *fn) const
{
  auto& meta = sampler.metadata();
  auto fn_ty = fn->getFunctionType();

  auto possibles = meta.live_with( [fn_ty] (auto inst) {
    return inst->getType() == fn_ty->getReturnType();
  });

  if(possibles.empty()) {
    return nullptr;
  }

  return B.CreateRet(util::uniform_sample(possibles));
}

template <typename R, typename... Args>
template <typename Builder>
void Linear<R, Args...>::create_oob_returns(Builder&& b, 
                                            ValueSampler& sampler, 
                                            llvm::Function *fn) const
{
  auto& meta = sampler.metadata();

  auto ret_ty = fn->getFunctionType()->getReturnType();
  auto zero = llvm::ConstantInt::get(ret_ty, 0);
  auto one = llvm::ConstantInt::get(ret_ty, 1);

  auto oob_bb = llvm::BasicBlock::Create(fn->getContext(), "oob-exit", fn);
  b.SetInsertPoint(oob_bb);
  b.CreateStore(one, fn->arg_begin()); 
  b.CreateRet(zero);

  for(auto oob_flag_val : meta.oob_flags()) {
    auto oob_flag = llvm::cast<llvm::Instruction>(oob_flag_val);

    auto old_bb = oob_flag->getParent();
    auto new_bb = old_bb->splitBasicBlock(oob_flag);

    auto old_term = old_bb->getTerminator();

    b.SetInsertPoint(old_term);
    auto br = b.CreateCondBr(oob_flag_val, oob_bb, new_bb);
    oob_flag->moveBefore(br);
    old_term->eraseFromParent();
  }
}

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Linear<R, Args...>::generate_candidate(bool& done)
{
  auto mod = std::make_unique<llvm::Module>("linear-candidate", ThreadContext::get());
  auto B = llvm::IRBuilder<>{mod->getContext()};

  while(!done) {
    clear_functions(*mod);

    auto sampler = ValueSampler{};
    auto& meta = sampler.metadata();

    auto fn = llvm::Function::Create(llvm_function_type(), llvm::GlobalValue::ExternalLinkage, 
                                     "cand", mod.get());
    auto bb = llvm::BasicBlock::Create(fn->getContext(), "", fn);
    B.SetInsertPoint(bb);

    util::index_for_each(arg_types_, [&](auto&& at, auto idx) {
      if constexpr(is_index(at)) {
        meta.set_index_bound(fn->arg_begin() + idx + 1, at.bound());
      }
    });

    populate_instructions(B, sampler, fn, 20);
    auto ret = create_return(B, sampler, fn);
    if(!ret) {
      return nullptr;
    }

    create_oob_returns(B, sampler, fn);

    if(satisfies_examples(fn)) {
      done = true;
      return std::move(mod);
    }
  }

  return nullptr;
}

template <typename R, typename... Args>
void Linear<R, Args...>::add_example(Linear::ret_t r, Linear::args_t args)
{
  examples_.push_back({r, args});
}

template <typename R, typename... Args>
llvm::FunctionType *Linear<R, Args...>::llvm_function_type() const
{
  auto llvm_arg_tys = std::array<llvm::Type*, sizeof...(Args)>{};
  util::zip_for_each(arg_types_, llvm_arg_tys, [] (auto a, auto& ll) {
    ll = a.llvm_type();
  });

  auto i64_t = llvm::IntegerType::get(ThreadContext::get(), 64);
  auto ptr_t = llvm::PointerType::getUnqual(i64_t);
  auto arg_tys = std::array<llvm::Type*, sizeof...(Args) + 1>{};
  std::copy(std::begin(llvm_arg_tys), std::end(llvm_arg_tys), std::next(std::begin(arg_tys)));
  arg_tys[0] = ptr_t;

  return llvm::FunctionType::get(return_type_.llvm_type(), arg_tys, false);
}

template <typename R, typename... Args>
bool Linear<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = FunctionCallable<ret_t>{f, true};

  return std::all_of(std::begin(examples_), std::end(examples_), [f,&fc](auto ex) {
    return std::apply(fc, ex.second) == ex.first;
  });
}

template <typename R, typename... Args>
void Linear<R, Args...>::clear_functions(llvm::Module& module)
{
  auto to_clear = std::forward_list<llvm::Function *>{};

  for(auto& f : module) {
    if(f.getName() == "cand") {
      to_clear.push_front(&f);
    }
  }

  for(auto* f : to_clear) {
    f->eraseFromParent();
  }
}

}
