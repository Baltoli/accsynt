#pragma once

#include <props/core.h>
#include <support/tuple.h>

#include <optional>
#include <tuple>
#include <type_traits>

namespace props {

struct any_ptr_st {
};

constexpr inline any_ptr_st any_ptr = any_ptr_st{};

template <typename F>
class on {
  static_assert(std::is_invocable_v<F, param const&> || std::is_invocable_v<F>,
      "Visitor function must be invocable with param or no args");

  static constexpr bool pass_param = std::is_invocable_v<F, param const&>;

public:
  on(base_type dt, F&& f);
  on(base_type dt, int depth, F&& f);
  on(base_type dt, any_ptr_st, F&& f);

  void operator()(param const& p);

private:
  base_type dt_;
  bool any_depth_;
  std::optional<int> depth_;
  F f_;
};

template <typename F>
on(base_type, F &&)->on<F>;

template <typename F>
on(base_type, int, F &&)->on<F>;

template <typename F>
on(base_type, any_ptr_st, F &&)->on<F>;

template <typename F>
on<F>::on(base_type dt, F&& f)
    : dt_(dt)
    , any_depth_(false)
    , depth_()
    , f_(std::forward<F>(f))
{
}

template <typename F>
on<F>::on(base_type dt, int depth, F&& f)
    : dt_(dt)
    , any_depth_(false)
    , depth_(depth)
    , f_(std::forward<F>(f))
{
}

template <typename F>
on<F>::on(base_type dt, any_ptr_st, F&& f)
    : dt_(dt)
    , any_depth_(true)
    , depth_(0)
    , f_(std::forward<F>(f))
{
}

template <typename F>
void on<F>::operator()(param const& p)
{
  if (dt_ == p.type) {
    if (depth_ && !any_depth_) {
      if (*depth_ == p.pointer_depth) {
        if constexpr (pass_param) {
          f_(p);
        } else {
          f_();
        }
      }
    } else if (any_depth_) {
      if (p.pointer_depth != 0) {
        if constexpr (pass_param) {
          f_(p);
        } else {
          f_();
        }
      }
    } else if (p.pointer_depth == 0) {
      if constexpr (pass_param) {
        f_(p);
      } else {
        f_();
      }
    }
  }
}

template <typename... Fs>
class sig_visitor {
public:
  sig_visitor(Fs&&... fns);
  void visit(signature const& sig);

private:
  std::tuple<Fs...> fns_;
};

template <typename... Fs>
sig_visitor<Fs...>::sig_visitor(Fs&&... fns)
    : fns_(std::forward<Fs>(fns)...)
{
}

template <typename... Fs>
void sig_visitor<Fs...>::visit(signature const& sig)
{
  for (auto const& param : sig.parameters) {
    support::for_each(fns_, [&](auto& fn) { fn(param); });
  }
}

} // namespace props
