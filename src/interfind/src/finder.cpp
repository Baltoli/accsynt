#include <interfind/finder.h>
#include <interfind/region.h>

#include <llvm/IR/Module.h>

#include <nlohmann/json.hpp>

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

  for(auto& fn : mod) {
    if(!fn.isDeclaration()) {
      auto rf = region_finder(fn, sig_t);

      for(auto cand : rf.all_candidates()) {
        auto f = cand.extract();
      }
    }
  }

  return {};
}

}
