#include <props/props.h>

#include <set>
#include <tuple>

namespace props {

size_t base_type_size(base_type dt)
{
  switch (dt) {
  case base_type::character:
  case base_type::boolean:
    return 1;
  case base_type::floating:
    return 4;
  case base_type::integer:
    return 8;
  }

  throw std::runtime_error("Invalid type");
}

bool data_type::operator==(data_type const& other) const
{
  return std::tie(base, pointers) == std::tie(other.base, other.pointers);
}

bool data_type::operator!=(data_type const& other) const
{
  return !(*this == other);
}

size_t signature::param_index(std::string const& name) const
{
  size_t idx = 0;
  for (auto const& param : parameters) {
    if (param.name == name) {
      return idx;
    }
    ++idx;
  }

  throw std::runtime_error("Invalid name to get index for");
}

bool signature::accepts_pointer() const
{
  bool any = false;
  auto make_true = [&any] { any = true; };

  // clang-format off
  sig_visitor{
    on(base_type::boolean,    any_ptr, make_true),
    on(base_type::integer,    any_ptr, make_true),
    on(base_type::character,  any_ptr, make_true),
    on(base_type::floating,   any_ptr, make_true)
  }.visit(*this);
  // clang-format on

  return any;
}

bool property_set::is_valid() const
{
  auto param_names = std::set<std::string_view> {};
  for (auto const& param : type_signature.parameters) {
    auto [iter, ins] = param_names.insert(param.name);
    if (!ins) {
      return false; // Non-unique parameter name
    }
  }

  for (auto const& prop : properties) {
    for (auto const& val : prop.values) {
      if (val.value_type == value::type::parameter) {
        auto found = param_names.find(val.param_val);
        if (found == param_names.end()) {
          return false;
        }
      }
    }
  }

  return true;
}

bool value::is_int() const { return value_type == type::integer; }
bool value::is_float() const { return value_type == type::floating; }
bool value::is_param() const { return value_type == type::parameter; }
bool value::is_string() const { return value_type == type::string; }

bool value::operator==(value const& other) const
{
  if (value_type != other.value_type) {
    return false;
  }

  switch (value_type) {
  case type::integer:
    return int_val == other.int_val;
  case type::floating:
    return float_val == other.float_val;
  case type::parameter:
    return param_val == other.param_val;
  case type::string:
    return string_val == other.string_val;
  }

  return false;
}

bool value::operator!=(value const& other) const { return !(*this == other); }
} // namespace props
