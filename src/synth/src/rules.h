#pragma once

#include <support/visitor.h>

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

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_expression const& m)
  {
    auto bind_str = support::visitor{
      [] (std::string s) { return s; },
      [] (ignore_value) { return std::string("_"); }
    };

    os << "match(";
    auto comma = "";
    for(auto b : m.bindings_) {
      os << comma << std::visit(bind_str, b);
      comma = ", ";
    }
    os << ")";
    return os;
  }

protected:
  std::string property_name_;
  std::vector<binding_t> bindings_;
};

}
