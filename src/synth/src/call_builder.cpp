#include "call_builder.h"

using namespace llvm;
using namespace props;

namespace synth {

call_builder::call_builder(props::signature sig) :
  signature_(sig)
{
}

signature const& call_builder::signature() const
{
  return signature_;
}

uint8_t* call_builder::args()
{
  return args_.data();
}

bool call_builder::operator==(call_builder const& other) const
{
  // Easy up front checks - we need to be storing the same quantity of argument
  // data, and we need the same signature.
  if(args_.size() != other.args_.size()) {
    return false;
  }

  if(signature_ != other.signature_) {
    return false;
  }

  // Offset into the raw byte data - updated for each parameter we see during
  // our iteration. Skips over pointers
  size_t offset = 0;

  // Offsets into the stored data vectors - updated each time we see a
  // parameter of the appropriate data type.
  size_t int_data_offset = 0;
  size_t float_data_offset = 0;

  bool all_eq = true;

  for(auto const& param : signature_.parameters) {
    if(!all_eq) {
      return false;
    }

    if(param.pointer_depth == 0) {
      // Value comparisons done on the raw byte data
      // TODO: fix hard-coded size assumption when I have more types
      for(auto i = 0u; i < 4; ++i, ++offset) {
        all_eq = all_eq && (args_.at(offset) == other.args_.at(offset));
      }
    } else {
      // Pointer comparisons need to look at the data stored, and need to ignore
      // 8 bytes of the stored argument bytes as well - pointers will be
      // different
      offset += 8;

      if(param.type == data_type::integer) {
        all_eq = all_eq && 
          (int_data_.at(int_data_offset) == 
           other.int_data_.at(int_data_offset));
      } else if(param.type == data_type::floating) {
        all_eq = all_eq && 
          (float_data_.at(float_data_offset) == 
           other.float_data_.at(float_data_offset));
      }
    }
  }

  return all_eq;
}

bool call_builder::operator!=(call_builder const& other) const
{
  return !(*this == other);
}

}
