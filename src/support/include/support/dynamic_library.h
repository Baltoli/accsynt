#pragma once

#include <dlfcn.h>
#include <exception>
#include <stdexcept>
#include <string>

namespace support {

class dyld_error : public std::exception {
public:
  dyld_error(char const* err);

  char const* what() const noexcept override;

private:
  char const* str_;
};

class dynamic_library {
public:
  explicit dynamic_library(const std::string& path);

  dynamic_library(dynamic_library const&) = delete;
  dynamic_library& operator=(dynamic_library const&) = delete;

  dynamic_library(dynamic_library&&);
  dynamic_library& operator=(dynamic_library&&);

  ~dynamic_library();

  template <typename Func>
  Func* symbol(const std::string& sym) const;

  void* raw_symbol(const std::string& sym) const;

private:
  void* lib_;
};

template <typename Func>
Func* dynamic_library::symbol(const std::string& sym) const
{
  return reinterpret_cast<Func*>(raw_symbol(sym));
}

} // namespace support
