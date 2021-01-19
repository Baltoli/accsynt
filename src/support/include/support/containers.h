#include <functional>

namespace support {

template <typename Set, typename Pred>
typename Set::size_type erase_if(Set& set, Pred&& p)
{
  using std::begin;
  using std::end;

  auto count = typename Set::size_type(0);

  auto b = begin(set);
  auto e = end(set);

  for (auto it = b; it != e; ++it) {
    if (std::invoke(std::forward<Pred>(p), *it)) {
      ++count;

      auto next_it = std::next(it);
      set.erase(it);
      it = next_it;

      if (it == e) {
        break;
      } else {
        continue;
      }
    }
  }

  return count;
}

} // namespace support
