#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// TODO: abstract parser state from PODs used for domain

namespace props {

struct property_set;

enum class data_type { integer, floating };

llvm::Type* base_llvm_type(data_type dt);
llvm::Type* base_llvm_return_type(std::optional<data_type> dt);

struct param {
  std::string name;
  data_type type;
  int pointer_depth;

  llvm::Type* llvm_type() const;

  bool operator==(param const& other) const;
  bool operator!=(param const& other) const;
};

struct signature {
  signature() = default;

  std::optional<data_type> return_type;
  std::string name;
  std::vector<param> parameters;

  size_t param_index(std::string const& name) const;

  llvm::FunctionType* function_type() const;
  llvm::Function* create_function(llvm::Module& mod) const;

  static signature parse(std::string_view str);

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  signature(Input const& in, property_set& parent)
  {
  }

  bool operator==(signature const& other) const;
  bool operator!=(signature const& other) const;
};

// clang-format off
template <
  typename OnInt, 
  typename OnFloat, 
  typename OnIntPtr,
  typename OnFloatPtr
>
struct sig_visitor {
  static constexpr bool pass_depth = 
    std::is_invocable_v<OnInt> && std::is_invocable_v<OnFloat> &&
    std::is_invocable_v<OnIntPtr, int> && std::is_invocable_v<OnFloatPtr, int>;

  static constexpr bool pass_param =
    std::is_invocable_v<OnInt, param> && std::is_invocable_v<OnFloat, param> &&
    std::is_invocable_v<OnIntPtr, param> && std::is_invocable_v<OnFloatPtr, param>;

  static_assert(pass_depth != pass_param, "Must be unambiguous");

  static constexpr bool return_void = pass_depth ?
    std::is_same_v<std::invoke_result_t<OnInt>, void> :
    std::is_same_v<std::invoke_result_t<OnInt, int>, void>;

  using pass_depth_ret = std::common_type<
    std::invoke_result_t<OnInt>, std::invoke_result_t<OnFloat>,
    std::invoke_result_t<OnIntPtr, int>, std::invoke_result_t<OnFloatPtr, int>
  >;

  using pass_param_ret = std::common_type<
    std::invoke_result_t<OnInt, param>, std::invoke_result_t<OnFloat, param>,
    std::invoke_result_t<OnIntPtr, param>, std::invoke_result_t<OnFloatPtr, param>
  >;

  using return_type = std::conditional_t<return_void,
    void,
    std::vector<
      typename std::conditional_t<pass_depth, pass_depth_ret, pass_param_ret>::type
    >
  >;

public:
  // Either they are all invocable with:
  // (), (), (int), (int)
  // or with:
  // (param), (param), (param), (param)
  sig_visitor(OnInt oi, OnFloat of, OnIntPtr oip, OnFloatPtr ofp) : on_int_(oi),
      on_float_(of), on_int_ptr_(oip), on_float_ptr_(ofp)
  {
  }

  return_type visit(signature const&) const
  {
  }

private:
  OnInt on_int_;
  OnFloat on_float_;
  OnIntPtr on_int_ptr_;
  OnFloatPtr on_float_ptr_;
};
// clang-format on

struct value {
  enum class type { integer, floating, parameter, string };

  type value_type;
  int int_val;
  float float_val;
  std::string param_val;
  std::string string_val;

  bool operator==(value const& other) const;
  bool operator!=(value const& other) const;

  static value with_int(int i);
  static value with_float(float f);
  static value with_param(std::string param);
  static value with_string(std::string str);

  bool is_int() const;
  bool is_float() const;
  bool is_param() const;
  bool is_string() const;

  template <typename OStream>
  friend OStream& operator<<(OStream& os, value const& v)
  {
    switch (v.value_type) {
    case type::integer:
      os << v.int_val;
      break;
    case type::floating:
      os << v.float_val;
      break;
    case type::parameter:
      os << v.param_val;
      break;
    case type::string:
      os << "\"" << v.string_val << "\"";
      break;
    }
    return os;
  }
};

struct property {
  property() = default;

  std::string name;
  std::vector<value> values;

  static property parse(std::string_view str);

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  property(Input const& in, property_set& parent)
  {
  }
};

class property_set {
public:
  signature type_signature;
  std::vector<property> properties;

  template <typename Func>
  void for_each_named(std::string const& name, Func&& fn) const;

  static property_set parse(std::string_view str);
  static property_set load(std::string_view str);

private:
  bool is_valid() const;
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

template <typename Func>
void property_set::for_each_named(std::string const& name, Func&& fn) const
{
  for (auto const& prop : properties) {
    if (prop.name == name) {
      fn(prop);
    }
  }
}

namespace literals {

signature operator""_sig(const char* str, size_t len);

} // namespace literals

} // namespace props

std::ostream& operator<<(std::ostream& os, const props::data_type& dt);
std::ostream& operator<<(std::ostream& os, const props::param& p);
std::ostream& operator<<(std::ostream& os, const props::signature& sig);
