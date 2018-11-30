#pragma once

#include <string>
#include <variant>
#include <vector>

namespace synth {

struct ignore_value {};

class match_expression {
  using binding_t = std::variant<
    std::string,
    ignore_value
  >;

public:
  match_expression(std::string name, std::vector<binding_t> bs) :
    property_name_(name), bindings_(bs)
  {
  }

  template <typename... Args>
  match_expression(std::string name, Args... args) :
    match_expression(name, {args...})
  {
  }

private:
  std::string property_name_;
  std::vector<binding_t> bindings_;
};

template <typename OStream>
OStream& operator<<(OStream& os, match_expression const& m)
{
  os << "match()";
  return os;
}

}
