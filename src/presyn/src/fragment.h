#pragma once

#include "parameter.h"
#include "sketch_context.h"

#include <support/assert.h>
#include <support/traits.h>

#include <fmt/format.h>

#include <llvm/IR/BasicBlock.h>

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

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
  [[nodiscard]] virtual std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) = 0;

  /**
   * Because the core composition logic is defined virtually, we can use a
   * templated base class method to define composition in cases where we don't
   * have a UP already constructed.
   */
  template <typename Fragment>
  [[nodiscard]] std::enable_if_t<
      !support::is_unique_ptr_v<std::decay_t<Fragment>>,
      std::unique_ptr<fragment>>
  compose(Fragment&&);

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
   * Fragments represent part of a function sketch. To instantiate a fragment
   * into real code, the only knowledge required is the sketch context (for
   * information such as parameter types), and the basic block to direct all
   * control flow to when this fragment exits.
   *
   * Compilation is the primary mechanism by which the behaviour of fragments
   * can be observed - generally, they're abstract black boxes.
   *
   * In most cases, compilation of fragments proceeds recursively into the child
   * fragments according to the pre-defined semantics of that fragment (e.g. seq
   * will compile such that its first fragment executes, then the second).
   */
  [[nodiscard]] virtual llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const = 0;

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

  /**
   * Because this is an abstract base class, it needs a virtual destructor to
   * make sure that derived classes are deleted correctly.
   */
  virtual ~fragment() = default;

protected:
  template <typename... Children>
  static std::array<
      std::reference_wrapper<std::unique_ptr<fragment>>, sizeof...(Children)>
  children_ref(Children&...);

  template <typename Derived, typename... Children>
  std::unique_ptr<fragment>
  compose_generic(std::unique_ptr<fragment>&&, Children&...);
};

/**
 * A hole fragment generates no behaviour, and will accept any fragment for
 * composition.
 */
class hole final : public fragment {
public:
  hole() = default;

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;
};

/**
 * An empty fragment will generate no behaviour, and acts as an eliminator under
 * composition.
 *
 * This is semantically different from a hole - empty acts as a placeholder to
 * denote "no composition", while holes are the building blocks.
 */
class empty final : public fragment {
public:
  empty() = default;

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

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
  linear(std::unique_ptr<parameter>&&);

  linear(int);

  /**
   * There's room for some semantics-based optimisations and algebraic
   * properties here - by "crossing the 4th wall", if this is composed with
   * another linear fragment you can merge them. It violates the strict
   * compositionality idea but would reduce the size / complexity /
   * compilation time.
   */
  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> instructions_;
};

/**
 * A fragment that represents two fragments being executed in sequence one after
 * the other.
 *
 * Composition is defined using acceptance - if the *first* element in the
 * sequence accepts, then it receives the composition. If it does not and the
 * second one does, similarly. If neither does, this fragment does not accept
 * either.
 *
 * The acceptance-based composition is only used if this fragment is partially
 * empty: i.e. it does not yet have an F or G as used above.
 */
class seq final : public fragment {
public:
  seq();

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<fragment> first_;
  std::unique_ptr<fragment> second_;
};

/**
 * Represents a general while-loop:
 *
 *   while(cond) { body }
 *
 * Has only one child (the loop body), and is not parameterised on any
 * contextual information.
 *
 * Composition is simple: accepts once for the loop body, then passes
 * responsibility to children.
 */
class loop final : public fragment {
public:
  loop();

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<fragment> body_;
};

/**
 * Represents a loop that breaks when the pointer parameter derefences to a
 * particular value:
 *
 *   while(*ptr != ?) { body }
 *
 * Composition is as usually defined.
 */
class delimiter_loop final : public fragment {
public:
  delimiter_loop(std::string);
  delimiter_loop(std::unique_ptr<parameter>&&);

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> pointer_;
  std::unique_ptr<fragment> body_;
};

/**
 * Represents a loop to a fixed upper bound over a pointer ptr:
 *
 *   for(int i = 0; i < N; ++i) { body }
 *
 * Composition is defined as usual.
 */
class fixed_loop final : public fragment {
public:
  fixed_loop(std::string, std::string);
  fixed_loop(std::unique_ptr<parameter>&&, std::unique_ptr<parameter>&&);

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> pointer_;
  std::unique_ptr<parameter> size_;
  std::unique_ptr<fragment> body_;
};

class fixed_loop_new final : public fragment {
public:
  fixed_loop_new(
      std::unique_ptr<parameter>&&, std::vector<std::unique_ptr<parameter>>&&);

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> size_;
  std::vector<std::unique_ptr<parameter>> pointers_;
  std::unique_ptr<fragment> body_;
};

/**
 * Represents a conditional statement with no else branch:
 *
 *   if(P) { body }
 */
class if_ final : public fragment {
public:
  if_();

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  std::string to_string() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

private:
  std::unique_ptr<fragment> body_;
};

/**
 * Represents a conditional statement with true and false branches:
 *
 *   if(P) { body } else { else_body }
 */
class if_else final : public fragment {
public:
  if_else();

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<fragment> body_;
  std::unique_ptr<fragment> else_body_;
};

/**
 * Represents a let-binding of an affine index expression, parameterised on a
 * pointer into which we perform the indexing. Has a fragment body, which is the
 * context within which the index may be used:
 *
 *   let idx = {affine into ptr} in body
 */
class affine final : public fragment {
public:
  affine(std::string);
  affine(std::unique_ptr<parameter>&&);

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> pointer_;
  std::unique_ptr<fragment> body_;
};

/**
 * Similarly to affine, represents a let-binding of a general indexing
 * expression into its pointer parameter:
 *
 *   let idx = {idx into ptr} in body
 */
class index final : public fragment {
public:
  index(std::string);
  index(std::unique_ptr<parameter>&&);

  [[nodiscard]] std::unique_ptr<fragment>
  compose(std::unique_ptr<fragment>&&) override;

  bool accepts() const override;

  [[nodiscard]] llvm::BasicBlock*
  compile(sketch_context&, llvm::BasicBlock*) const override;

  std::string to_string() const override;

private:
  std::unique_ptr<parameter> pointer_;
  std::unique_ptr<fragment> body_;
};

// Implementations

template <typename Fragment>
[[nodiscard]] std::enable_if_t<
    !support::is_unique_ptr_v<std::decay_t<Fragment>>,
    std::unique_ptr<fragment>>
fragment::compose(Fragment&& other)
{
  return compose(std::make_unique<Fragment>(std::forward<Fragment>(other)));
}

template <typename... Children>
std::array<
    std::reference_wrapper<std::unique_ptr<fragment>>, sizeof...(Children)>
fragment::children_ref(Children&... chs)
{
  return {std::ref(chs)...};
}

template <typename Derived, typename... Children>
std::unique_ptr<fragment>
fragment::compose_generic(std::unique_ptr<fragment>&& other, Children&... chs)
{
  support::in_debug([&] {
    for (std::unique_ptr<fragment>& ch : children_ref(chs...)) {
      assumes(ch, "Child fragment in generic composition should not be null");
    }
  });

  for (std::unique_ptr<fragment>& ch : children_ref(chs...)) {
    if (ch->accepts()) {
      ch = ch->compose(std::move(other));
      break;
    }
  }

  assertion(
      dynamic_cast<Derived*>(this) != nullptr,
      "Generic composition being used badly");

  return std::make_unique<Derived>(std::move(*(static_cast<Derived*>(this))));
}

namespace literals {

std::unique_ptr<fragment> operator""_frag(const char* str, size_t len);

} // namespace literals

} // namespace presyn

template <>
struct fmt::formatter<presyn::fragment> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(presyn::fragment const& frag, FormatContext& ctx)
  {
    return format_to(ctx.out(), "{}", frag.to_string());
  }
};
