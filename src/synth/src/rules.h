#pragma once

#include <props/props.h>

#include <support/visitor.h>

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace synth {

struct ignore_value {};

class match_result {
public:
  match_result(std::map<std::string, props::value>);

  std::optional<match_result> unify_with(match_result const& other);

  template <typename Iterator>
  static std::optional<match_result> unify_all(Iterator begin, Iterator end);

  template <typename Container>
  static std::optional<match_result> unify_all(Container&& c);

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_result const& mr);

protected:
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
  match_expression(std::string name, Args... args);

  std::vector<match_result> match(props::property_set ps);

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_expression const& m);

protected:
  std::string property_name_;
  std::vector<binding_t> bindings_;
};

template <typename Iterator>
std::optional<match_result> match_result::unify_all(Iterator begin, Iterator end)
{
  if(begin == end) {
    return std::nullopt;
  }

  auto accum = std::optional<match_result>{*begin};
  for(auto it = begin; it != end && accum; ++it) {
    accum = accum->unify_with(*it);
  }

  return accum;
}

template <typename Container>
std::optional<match_result> match_result::unify_all(Container&& c)
{
  using std::begin;
  using std::end;
  return unify_all(begin(c), end(c));
}

template <typename OStream>
OStream& operator<<(OStream& os, match_result const& mr)
{
  os << "{";
  auto comma = "";
  for(auto [name, val] : mr.results_) {
    os << comma << name << ": " << val;
    comma = ", ";
  }
  os << "}";

  return os;
}

template <typename... Args>
match_expression::match_expression(std::string name, Args... args) :
  match_expression(name, {args...})
{
}

template <typename OStream>
OStream& operator<<(OStream& os, match_expression const& m)
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

}
