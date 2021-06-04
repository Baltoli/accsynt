#include <replacer/replace.h>

#include <support/assert.h>
#include <support/llvm_format.h>

#include <llvm/IR/Instructions.h>

using namespace llvm;

using json = ::nlohmann::json;

namespace idlr {

name_map collect_names(Function& fn)
{
  auto names = std::unordered_map<std::string, Value*> {};

  auto visit = [&names](auto& v) {
    if (v.hasName()) {
      names[v.getName().str()] = &v;
    }
  };

  visit(fn);

  for (auto& bb : fn) {
    visit(bb);

    for (auto& inst : bb) {
      visit(inst);
    }
  }

  return names;
}

replacer::replacer(llvm::Module& mod)
    : mod_(mod)
    , map_cache_()
{
}

void replacer::apply(spec const& sp)
{
  auto fn = mod_.getFunction(sp.function());
  assertion(fn, "Invalid spec: no function named {}", sp.function());

  if (map_cache_.find(fn) == map_cache_.end()) {
    map_cache_[fn] = collect_names(*fn);
  }

  for (auto const& [tgt, rep] : sp.replacements()) {
    apply(tgt, rep, *fn);
  }
}

void replacer::apply(
    std::string const& target, call const& new_v, llvm::Function& fn)
{
  auto& names = map_cache_[&fn];

  auto get_name = [&](auto const& name) {
    assertion(
        names.find(name) != names.end(),
        "Couldn't apply replacement {}: no value named {}", new_v, name);
    return names[name];
  };

  auto value = get_name(target);

  auto arg_vals = std::vector<Value*> {};
  for (auto const& arg : new_v.args()) {
    arg_vals.push_back(get_name(arg));
  }

  auto arg_types = std::vector<Type*> {};
  for (auto av : arg_vals) {
    arg_types.push_back(av->getType());
  }

  auto fn_t = FunctionType::get(value->getType(), arg_types, false);
  auto new_fn = fn.getParent()->getOrInsertFunction(new_v.target(), fn_t);

  auto new_call = CallInst::Create(
      new_fn, arg_vals, fmt::format("{}_rep", value->getName()),
      isa<Instruction>(value) ? dyn_cast<Instruction>(value) : nullptr);

  value->replaceAllUsesWith(new_call);

  if (auto i_val = dyn_cast<Instruction>(value)) {
    i_val->eraseFromParent();
  }

  names.erase(target);
}

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

