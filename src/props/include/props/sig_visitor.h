#pragma once

#include <props/core.h>

namespace props {

// clang-format off
template <
  typename OnInt, 
  typename OnFloat,
  typename OnIntPtr,
  typename OnFloatPtr
>
struct sig_visitor {
  using param_t = param const&;

  static constexpr bool pass_depth = 
    std::is_invocable_v<OnInt> && std::is_invocable_v<OnFloat> &&
    std::is_invocable_v<OnIntPtr, int> && std::is_invocable_v<OnFloatPtr, int>;

  static constexpr bool pass_param =
    std::is_invocable_v<OnInt, param_t> && std::is_invocable_v<OnFloat, param_t> &&
    std::is_invocable_v<OnIntPtr, param_t> && std::is_invocable_v<OnFloatPtr, param_t>;

  static_assert(pass_depth || pass_param, "Must be invokable");

  using one_return_t = typename std::conditional_t<pass_depth,
    std::invoke_result<OnInt>,
    std::invoke_result<OnInt, param_t>
  >::type;

  static constexpr bool return_void = std::is_same_v<one_return_t, void>;

  using return_type = std::conditional_t<return_void,
    void,
    std::vector<one_return_t>
  >;
  // clang-format on

public:
  // Either they are all invocable with:
  // (), (), (int), (int)
  // or with:
  // (param), (param), (param), (param)
  sig_visitor(OnInt oi, OnFloat of, OnIntPtr oip, OnFloatPtr ofp)
      : on_int_(oi)
      , on_float_(of)
      , on_int_ptr_(oip)
      , on_float_ptr_(ofp)
  {
  }

  return_type visit(signature const& sig) const
  {
    if constexpr (return_void) {
      for (auto const& p : sig.parameters) {
        if (p.pointer_depth == 0) {
          if (p.type == data_type::integer) {
            if constexpr (pass_depth) {
              on_int_();
            } else {
              on_int_(p);
            }
          } else if (p.type == data_type::floating) {
            if constexpr (pass_depth) {
              on_float_();
            } else {
              on_float_(p);
            }
          }
        } else {
          if (p.type == data_type::integer) {
            if constexpr (pass_depth) {
              on_int_ptr_(p.pointer_depth);
            } else {
              on_int_ptr_(p);
            }
          } else if (p.type == data_type::floating) {
            if constexpr (pass_depth) {
              on_float_ptr_(p.pointer_depth);
            } else {
              on_float_ptr_(p);
            }
          }
        }
      }
    } else {
      auto vec = return_type{};
      for (auto const& p : sig.parameters) {
        if (p.pointer_depth == 0) {
          if (p.type == data_type::integer) {
            if constexpr (pass_depth) {
              vec.push_back(on_int_());
            } else {
              vec.push_back(on_int_(p));
            }
          } else if (p.type == data_type::floating) {
            if constexpr (pass_depth) {
              vec.push_back(on_float_());
            } else {
              vec.push_back(on_float_(p));
            }
          }
        } else {
          if (p.type == data_type::integer) {
            if constexpr (pass_depth) {
              vec.push_back(on_int_ptr_(p.pointer_depth));
            } else {
              vec.push_back(on_int_ptr_(p));
            }
          } else if (p.type == data_type::floating) {
            if constexpr (pass_depth) {
              vec.push_back(on_float_ptr_(p.pointer_depth));
            } else {
              vec.push_back(on_float_ptr_(p));
            }
          }
        }
      }
      return vec;
    }
  }

private:
  OnInt on_int_;
  OnFloat on_float_;
  OnIntPtr on_int_ptr_;
  OnFloatPtr on_float_ptr_;
};

struct ignore_param_t {
  void operator()() const {}
  void operator()(int) const {}
  void operator()(param const&) const {}
};

extern ignore_param_t ignore_param;

} // namespace props
