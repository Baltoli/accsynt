#include <interfind/finder.h>
#include <interfind/region.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <nlohmann/json.hpp>

#include <passes/passes.h>

using namespace llvm;
using namespace props;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace interfind {

finder::finder(llvm::Module& mod, nlohmann::json conf) :
  module_(mod),
  signature_(signature::parse(conf["signature"].get<std::string>())),
  library_path_(conf["library_path"].get<std::string>())
{
  if(!fs::exists(library_path_)) {
    throw std::runtime_error("No such shared library");
  }
}

analysis_result finder::run(Module& mod, json config)
{
  auto find = finder(mod, config);
  auto sig_t = find.signature_.function_type();

  auto fns = std::vector<Function *>{};

  for(auto& fn : mod) {
    if(!fn.isDeclaration()) {
      fns.push_back(&fn);
    }
  }

  for(auto fn : fns) {
    createDeduplicatePass()->runOnFunction(*fn);

    auto rf = region_finder(*fn, sig_t);

    for(auto cand : rf.all_candidates()) {
      auto f = cand.extract();
    }
  }

  return {};
}

}
