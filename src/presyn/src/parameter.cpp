#include "parameter.h"

#include <fmt/format.h>

#include <support/assert.h>

namespace presyn {

using namespace fmt::literals;

// Constant ints

constant_int::constant_int(int v)
    : value_(v)
{
}

llvm::Type* constant_int::type() const { unimplemented(); }

llvm::Value* constant_int::get() const { unimplemented(); }

std::string constant_int::to_string() const { return "{}"_format(value_); }

// Named parameters

named::named(std::string n)
    : type_(nullptr)
    , name_(n)
{
}

llvm::Type* named::type() const { unimplemented(); }

llvm::Value* named::get() const { unimplemented(); }

std::string named::to_string() const { return "@{}"_format(name_); }

} // namespace presyn
