#pragma once

#include <props/props.h>

#include <support/visitor.h>

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace synth {

struct ignore_value {};

class match_result {
public:
  match_result(std::map<std::string, props::value>);

private:
  std::map<std::string, props::value> results_;
};

class match_expression {
  using binding_t = std::variant<
    std::string,
    ignore_value
  >;

public:
  match_expression(std::string name, std::vector<binding_t> bs);

  template <typename... Args>
  match_expression(std::string name, Args... args) :
    match_expression(name, {args...})
  {
  }

  std::vector<match_result> match(props::property_set ps);

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
