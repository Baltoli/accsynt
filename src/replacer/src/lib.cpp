#include <replacer/replace.h>

using json = ::nlohmann::json;

namespace idlr {

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

