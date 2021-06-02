#include <replacer/replace.h>

#include <support/llvm_format.h>

using namespace llvm;

using json = ::nlohmann::json;

namespace idlr {

std::unordered_map<std::string, Value*> collect_names(Module& mod)
{
  auto names = std::unordered_map<std::string, Value*> {};

  auto visit = [&names](auto& v) {
    if (v.hasName()) {
      names[v.getName().str()] = &v;
    }
  };

  for (auto& fn : mod) {
    visit(fn);

    for (auto& bb : fn) {
      visit(bb);

      for (auto& inst : bb) {
        visit(inst);
      }
    }
  }

  return names;
}

replacer::replacer(llvm::Module& mod)
    : mod_(mod)
    , name_map_(collect_names(mod_))
{
  for (auto& [k, v] : name_map_) {
    fmt::print("{} -> {}\n", k, *v);
  }
}

void replacer::apply(spec const& sp) { }

call::call(json j)
    : target_(j["callee"])
    , args_(j["args"])
{
}

spec::spec(json j)
    : func_(j["function"])
    , replacements_()
{
  for (auto& obj : j["replacements"].items()) {
    replacements_.emplace(obj.key(), call(obj.value()));
  }
}

} // namespace idlr

