#pragma once

#include <dist/function_callable.h>
#include <dist/contexts.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <forward_list>
#include <thread>
#include <tuple>

namespace llvm {
  class Function;
  class Module;
}

namespace accsynt {

template <typename R, typename... Args>
class Synthesizer {
public:
  using ret_t = typename all_outputs<R, Args...>::type;
  using args_t = std::tuple<typename Args::example_t...>;

  Synthesizer(R r, Args... args) :
    return_type_(r), arg_types_(args...) 
  {
    auto *ev = std::getenv("ACCSYNT_NUM_THREADS");
    if(ev) {
      max_threads_ = std::stoi(ev);
    } else {
      max_threads_ = 1;
    }
  }

  std::unique_ptr<llvm::Module> generate_candidate(bool& done) const;

  virtual void construct(llvm::Function *f, llvm::IRBuilder<>& b) const {}

  virtual bool can_synthesize() const { return false; }

  std::unique_ptr<llvm::Module> operator()() const { return threaded_generate(); }

  args_t example() const
  {
    auto ret = args_t{};
    zip_for_each(ret, arg_types_, [&](auto& ex, auto a) {
      ex = a.generate();
    });
    return ret;
  };

  void add_example(ret_t ret, args_t args) 
  {
    examples_.insert_or_assign(args, ret);
  }

protected:
  llvm::FunctionType *llvm_function_type() const;
  bool satisfies_examples(llvm::Function *f) const;
  std::unique_ptr<llvm::Module> threaded_generate() const;

  R return_type_;
  std::tuple<Args...> arg_types_;

private:
  void clear_functions(llvm::Module& module) const;

  size_t max_threads_;
  std::map<args_t, ret_t> examples_ = {};
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Synthesizer<R, Args...>::generate_candidate(bool& done) const
{
  auto mod = std::make_unique<llvm::Module>("synth-candidate", ThreadContext::get());
  auto B = llvm::IRBuilder<>{mod->getContext()};

  while(!done) {
    clear_functions(*mod);

    auto fn = llvm::Function::Create(this->llvm_function_type(), llvm::GlobalValue::ExternalLinkage, 
                                     "cand", mod.get());
    auto bb = llvm::BasicBlock::Create(fn->getContext(), "entry", fn);
    B.SetInsertPoint(bb);

    this->construct(fn, B);

    if(satisfies_examples(fn)) {
      done = true;
      return std::move(mod);
    }
  }

  return nullptr;
}

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Synthesizer<R, Args...>::threaded_generate() const
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
  for(auto i = 0u; i < max_threads_; ++i) {
    threads.emplace_front(work);
  }

  for(auto& t : threads) {
    t.join();
  }

  return ret;
}

template <typename R, typename... Args>
llvm::FunctionType *Synthesizer<R, Args...>::llvm_function_type() const
{
  auto llvm_arg_tys = std::array<llvm::Type*, sizeof...(Args)>{};
  zip_for_each(arg_types_, llvm_arg_tys, [] (auto a, auto& ll) {
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
bool Synthesizer<R, Args...>::satisfies_examples(llvm::Function *f) const
{
  auto fc = std::apply([&](auto&&... args) {
    return FunctionCallable{with_error_code, f, return_type_, args...};
  }, arg_types_);

  return std::all_of(std::begin(examples_), std::end(examples_), [f,&fc](auto ex) {
    return std::apply(fc, ex.first) == ex.second;
  });
}

template <typename R, typename... Args>
void Synthesizer<R, Args...>::clear_functions(llvm::Module& module) const
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
