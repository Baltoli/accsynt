#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>

#include <exception>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// TODO: abstract parser state from PODs used for domain

namespace props {

class parse_error : public std::exception {
public:
  parse_error(char const*);

  char const* what() const noexcept override;

private:
  char const* str_;
};

class property_set;

enum class base_type { boolean, character, integer, floating };

size_t base_type_size(base_type dt);

llvm::Type* base_llvm_type(base_type dt);
llvm::Type* base_llvm_return_type(std::optional<base_type> dt);

// FIXME: This is a big hack and needs to be fixed properly in the future when I
// have time to do so. The functionality is duplicated between this struct and
// the rest of the code - see param below for the problem.
//
// It's a big but boring refactoring to change every usage of base_type to
// data_type where appropriate.
struct data_type {
  base_type base;
  size_t pointers;

  bool operator==(data_type const& other) const;
  bool operator!=(data_type const& other) const;

  static std::optional<data_type> from_llvm(llvm::Type*);
};

struct param {
  std::string name;
  base_type type;
  int pointer_depth;

  llvm::Type* llvm_type() const;

  bool compatible(param const& other) const;

  bool operator==(param const& other) const;
  bool operator!=(param const& other) const;
};

struct signature {
  signature() = default;

  std::optional<data_type> return_type;
  std::string name;
  std::vector<param> parameters;

  size_t param_index(std::string const& name) const;

  bool accepts_pointer() const;

  llvm::FunctionType* function_type() const;
  llvm::Function* create_function(llvm::Module& mod) const;

  static signature parse(std::string_view str);

  static std::optional<signature>
  from_llvm(llvm::FunctionType*, std::string name = "");

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  signature(Input const& in, property_set& parent)
  {
  }

  bool operator==(signature const& other) const;
  bool operator!=(signature const& other) const;
};

struct value {
  enum class type { integer, floating, parameter, string };

  type value_type;
  int64_t int_val;
  float float_val;
  std::string param_val;
  std::string string_val;

  bool operator==(value const& other) const;
  bool operator!=(value const& other) const;

  static value with_int(int64_t i);
  static value with_float(float f);
  static value with_param(std::string param);
  static value with_string(std::string str);

  bool is_int() const;
  bool is_float() const;
  bool is_param() const;
  bool is_string() const;
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
property_set operator""_ps(const char* str, size_t len);

} // namespace literals

} // namespace props
