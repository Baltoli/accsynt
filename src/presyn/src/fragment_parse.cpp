#include "fragment_parse.h"
#include "fragment.h"

#include <support/assert.h>

namespace presyn {

using namespace tao::pre_tl;

std::unique_ptr<fragment> build(grammar::fragment_parse const& parse)
{
  return nullptr;
}

std::unique_ptr<fragment> fragment::parse(std::string_view str)
{
  auto state = grammar::fragment_state{};

  tao::pre_tl::parse<must<grammar::fragment, eof>, grammar::fragment_action>(
      memory_input(str.begin(), str.end(), ""), state);

  assert(state.stack.empty() && "Parsing did not finish with empty stack");
  return build(state.result);
}

} // namespace presyn
