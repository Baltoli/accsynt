#include <support/choose.h>

#include <vector>

namespace support {

choose::choose(size_t n, size_t k)
    : elements_(n)
    , choice_size_(k)
{
}
} // namespace support
