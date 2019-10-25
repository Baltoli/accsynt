#include <support/call_builder.h>
#include <support/float_compare.h>

using namespace props;
using namespace support;

using namespace llvm;

namespace support {

call_builder::call_builder(props::signature sig)
    : signature_(sig)
{
}

signature const& call_builder::signature() const { return signature_; }

call_builder::call_builder(call_builder const& other)
    : signature_(other.signature_)
    , current_arg_(0)
    , int_data_(other.int_data_)
    , float_data_(other.float_data_)
    , char_data_(other.char_data_)
{
  args_.clear();

  size_t offset = 0;
  size_t int_offset = 0;
  size_t float_offset = 0;
  size_t char_offset = 0;

  for (auto const& param : signature_.parameters) {
    if (current_arg_ >= other.current_arg_) {
      break;
    }

    if (param.pointer_depth == 0) {
      // TODO: fix size for more types
      for (auto i = 0u; i < base_type_size(param.type); ++i, ++offset) {
        args_.push_back(other.args_.at(offset));
      }
    } else {
      assert(param.pointer_depth == 1 && "Can't copy nested pointers");

      void* data = nullptr;
      if (param.type == base_type::integer) {
        data = int_data_.at(int_offset++).data();
      } else if (param.type == base_type::character) {
        data = char_data_.at(char_offset++).data();
      } else if (param.type == base_type::floating) {
        data = float_data_.at(float_offset++).data();
      }

      for (auto i = 0u; i < sizeof(void*); ++i) {
        args_.push_back(detail::nth_byte(data, i));
      }

      offset += 8;
    }

    current_arg_++;
  }
}

void call_builder::reset() { *this = call_builder(signature_); }

call_builder& call_builder::operator=(call_builder other)
{
  swap(*this, other);
  return *this;
}

void swap(call_builder& left, call_builder& right)
{
  using std::swap;
  swap(left.signature_, right.signature_);
  swap(left.args_, right.args_);
  swap(left.current_arg_, right.current_arg_);
  swap(left.int_data_, right.int_data_);
  swap(left.float_data_, right.float_data_);
  swap(left.char_data_, right.char_data_);
}

uint8_t* call_builder::args()
{
  assert(current_arg_ == signature_.parameters.size()
      && "Argument pack not fully built yet!");
  return args_.data();
}

bool call_builder::operator==(call_builder const& other) const
{
  // Easy up front checks - we need to be storing the same quantity of
  // argument data, and we need the same signature.
  if (args_.size() != other.args_.size()) {
    return false;
  }

  if (signature_ != other.signature_) {
    return false;
  }

  // Offset into the raw byte data - updated for each parameter we see during
  // our iteration. Skips over pointers
  size_t offset = 0;

  // Offsets into the stored data vectors - updated each time we see a
  // parameter of the appropriate data type.
  size_t int_data_offset = 0;
  size_t float_data_offset = 0;
  size_t char_data_offset = 0;

  bool all_eq = true;

  for (auto const& param : signature_.parameters) {
    if (!all_eq) {
      return false;
    }

    if (param.pointer_depth == 0) {
      // Value comparisons done on the raw byte data
      for (auto i = 0u; i < base_type_size(param.type); ++i, ++offset) {
        all_eq = all_eq && (args_.at(offset) == other.args_.at(offset));
      }
    } else {
      // Pointer comparisons need to look at the data stored, and need to
      // ignore 8 bytes of the stored argument bytes as well - pointers will
      // be different
      offset += 8;

      if (param.type == base_type::integer) {
        all_eq = all_eq
            && (int_data_.at(int_data_offset)
                   == other.int_data_.at(int_data_offset));
        int_data_offset++;
      } else if (param.type == base_type::character) {
        all_eq = all_eq
            && (char_data_.at(char_data_offset)
                   == other.char_data_.at(char_data_offset));
        char_data_offset++;
      } else if (param.type == base_type::floating) {
        all_eq = all_eq
            && approx_equal(float_data_.at(float_data_offset),
                   other.float_data_.at(float_data_offset));
        float_data_offset++;
      }
    }
  }

  return all_eq;
}

bool call_builder::operator!=(call_builder const& other) const
{
  return !(*this == other);
}
} // namespace support
