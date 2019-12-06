#pragma once

#include <memory>
#include <string_view>

namespace presyn {

/*
 * Interfaces for the key types involved in creating a fragment from arguments
 * or a string.
 */

class type {
public:
};

class parameter {
public:
};

class fragment {
public:
  /**
   * Parse a fragment from a format string describing it. The logic for this is
   * essentially a factory pattern that dispatches on a parsed fragment name in
   * order to construct the correct type at runtime.
   */
  static std::unique_ptr<fragment> parse(std::string_view);

  /**
   * Compose this fragment with another one. This is an abstract operation, and
   * so it needs to be able to take ownership of the other fragment (e.g. to
   * save it until compile time when its compositional behaviour can be used).
   *
   * The consequence of this design is that fragments don't need to know the
   * internals of what they're being composed with (but can possibly in the
   * future make some kind of determinance about the behaviour of the other
   * fragment...).
   */
  virtual std::unique_ptr<fragment> compose(std::unique_ptr<fragment>&& other)
      = 0;

  /**
   * Compilation logic not yet implemented until the core of the actual
   * behaviour is built up.
   */
  /* virtual program compile() = 0; */
};

} // namespace presyn
