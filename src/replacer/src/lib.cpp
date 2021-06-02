#include <replacer/replace.h>

namespace idlr {

call::call(std::string t, std::vector<std::string> as)
    : target_(t)
    , args_(as)
{
}

spec::spec(std::string f, std::unordered_map<std::string, call> rs)
    : func_(f)
    , replacements_(rs)
{
}

} // namespace idlr
