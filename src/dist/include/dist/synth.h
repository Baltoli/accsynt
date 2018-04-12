#pragma once

#include <tuple>

namespace accsynt {

template <typename R, typename... Args>
class Synthesizer {
public:
  using ret_t = typename R::example_t;
  using args_t = std::tuple<typename Args::example_t...>;
  using io_pair_t = std::pair<ret_t, args_t>;

  Synthesizer(R r, Args... args) :
    return_type_(r), arg_types_(args...) {}

  args_t example() const {
    auto ret = args_t{};
    zip_for_each(ret, arg_types_, [&](auto& ex, auto a) {
      ex = a.generate();
    });
    return ret;
  };

protected:
  R return_type_;
  std::tuple<Args...> arg_types_;
};

}
