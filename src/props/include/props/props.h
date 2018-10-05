#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

// TODO: abstract parser state from PODs used for domain

namespace props::detail {

struct property_set;

enum class data_type {
  integer,
  floating
};

struct param {
  std::string name;
  data_type type;
  int pointer_depth;
};

struct signature {
  signature() = default;

  std::optional<data_type> return_type;
  std::string name;
  std::vector<param> parameters;

  static signature parse(std::string_view str);

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  signature(Input const& in, property_set& parent) {}
};

struct value {
  enum class type {
    integer,
    floating,
    parameter,
    string
  };

  type value_type;
  int int_val;
  float float_val;
  std::string param_val;
  std::string string_val;

  static value with_int(int i);
  static value with_float(float f);
  static value with_param(std::string param);
  static value with_string(std::string str);
};

struct property {
  property() = default;

  std::string name;
  std::vector<value> values;

  static property parse(std::string_view str);

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  property(Input const& in, property_set& parent) {}
};

struct property_set {
  signature type_signature;
  std::vector<property> properties;

  static property_set parse(std::string_view str);
};

template <typename Input>
void property::success(Input const& in, property_set& parent)
{
  parent.properties.push_back(*this);
}

template <typename Input>
void signature::success(Input const& in, property_set& parent)
{
  parent.type_signature = *this;
}

}

std::ostream& operator<<(std::ostream& os, const props::detail::data_type& dt);
std::ostream& operator<<(std::ostream& os, const props::detail::param& p);
std::ostream& operator<<(std::ostream& os, const props::detail::signature& sig);
