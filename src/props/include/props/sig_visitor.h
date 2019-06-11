#pragma once

#include <props/core.h>
#include <support/tuple.h>

#include <optional>
#include <tuple>

namespace props {

template <typename F>
class on {
public:
  on(data_type dt, F&& f);
  on(data_type dt, int depth, F&& f);

  void operator()(param const& p);

private:
  data_type dt_;
  std::optional<int> depth_;
  F f_;
};

template <typename F>
on<F>::on(data_type dt, F&& f)
    : dt_(dt)
    , depth_()
    , f_(std::forward<F>(f))
{
}

template <typename F>
on<F>::on(data_type dt, int depth, F&& f)
    : dt_(dt)
    , depth_(depth)
    , f_(std::forward<F>(f))
{
}

template <typename F>
void on<F>::operator()(param const& p)
{
  if (dt_ == p.type) {
    if (depth_) {
      if (*depth_ == p.pointer_depth) {
        f_(p);
      }
    } else if (p.pointer_depth == 0) {
      f_(p);
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
