#include <interfind/finder.h>

#include <llvm/IR/Module.h>

#include <nlohmann/json.hpp>

using namespace llvm;
using json = nlohmann::json;

namespace interfind {
  
analysis_result finder::run(Module& mod, json config)
{
  return {};
}

}
