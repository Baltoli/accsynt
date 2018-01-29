#include <dist/distinguisher.h>
#include <dist/utils.h>

#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <random>
#include <vector>

using namespace llvm;

/* std::optional<std::vector<GenericValue>> FunctionDistinguisher::operator()() const */
/* { */
/*   auto rd = std::random_device{}; */
/*   auto engine = std::default_random_engine(rd()); */
/*   auto dist = std::geometric_distribution<int32_t>{0.1}; */

/*   for(int i = 0; i < example_limit_; ++i) { */
/*     auto args = std::vector<GenericValue>(arg_size()); */
/*     for(auto i = 0; i < arg_size(); ++i) { */
/*       auto val = GenericValue{}; */
/*       val.IntVal = APInt(32, dist(engine), true); */
/*       args[i] = val; */
/*     } */

/*     auto f_ret = run_function(f_, args); */
/*     auto g_ret = run_function(g_, args); */

/*     if(f_ret.IntVal != g_ret.IntVal) { */
/*       return args; */
/*     } */
/*   } */ 

/*   return {}; */
/* } */
