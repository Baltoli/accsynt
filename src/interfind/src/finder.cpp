#include <interfind/finder.h>

#include <llvm/IR/Module.h>

#include <nlohmann/json.hpp>

using namespace llvm;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace interfind {

finder::config::config(std::string sig, std::string path) :
  signature(sig), library_path(path)
{
  if(!fs::exists(library_path)) {
    throw std::invalid_argument("Shared library does not exist");
  }
}

finder::config::config(json conf) :
  config(
      conf["signature"].get<std::string>(),
      conf["library_path"].get<std::string>())
{
}
  
finder::finder(llvm::Module& mod, nlohmann::json conf) :
  module_(mod), config_(conf)
{
}

analysis_result finder::run(Module& mod, json config)
{
  auto find = finder(mod, config);
  return {};
}

}
