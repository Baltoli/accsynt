#pragma once

#include "parameter.h"

#include <memory>
#include <string>
#include <string_view>

namespace presyn {

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
   *
   * Because this gets ownership of the parameter, it means that (for example)
   * an implementation could just return the original if it needs.
   *
   * Generally, the pattern that will be followed by implementations of this is
   * that they store up fragments until compilation, when they'll use the
   * exposed behaviour of their compositions to perform a compilation.
   */
  virtual std::unique_ptr<fragment> compose(std::unique_ptr<fragment>&&) = 0;

  /**
   * Any two fragments can be composed together, but the result may not actually
   * use the second fragment. For example:
   *
   *  empty * F = empty, for all F
   *
   * Additionally, some fragments may have multiple child fragments. For
   * example:
   *
   *  seq(F, G)
   *
   * In this example, we need to be able to define the semantics of composition
   * properly. That is, which of these is the correct result?
   *
   *  seq(F, G) * H = seq(F * H, G)
   *  seq(F, G) * H = seq(F, G * H)
   *
   * The way to define this is by allowing fragments to communicate when they
   * will *use* the result of a composition:
   *
   *  accepts(empty) = false
   *
   * So then:
   *
   *  seq(F, G) * H = seq(F * H, G) if accepts(F)
   *                = seq(F, G * H) if accepts(G)
   *                = seq(F, G)     else
   *
   * The semantics of accepts can then be defined recursively:
   *
   *  accepts(seq(F, G)) = accepts(F) || accepts(G)
   *
   * We can see that this will respect the definition of composition given
   * above: seq(F, G) only uses H in its compositions if it accepts. However,
   * the composition is still well-defined in this case.
   *
   * This relationship between acceptance and composition should be respected by
   * new fragment implementations.
   */
  virtual bool accepts() const = 0;

  /**
   * Compilation logic not yet implemented until the core of the actual
   * behaviour is built up.
   */
  /* virtual program compile() = 0; */

  /**
   * Get a representation of this type of fragment as a string for
   * pretty-printing.
   */
  virtual std::string to_string() const = 0;
};

/**
 * An empty fragment will generate no behaviour, and acts as an identity under
 * composition.
 */
class empty final : public fragment {
public:
  std::unique_ptr<fragment> compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  std::string to_string() const override;
};

/**
 * A linear fragment will produce a basic block of instructions (the number of
 * which is specified by a parameter - i.e. linear(2) produces 2 instructions,
 * and linear(0) would be equivalent to empty()). It acts as the identity for
 * composition.
 */
class linear final : public fragment {
public:
  linear(int);

  std::unique_ptr<fragment> compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  std::string to_string() const override;

private:
  int instructions_;
};

} // namespace presyn
