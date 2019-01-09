#include "data_loop_fragment.h"

using namespace props;

namespace synth {

data_loop_fragment::data_loop_fragment(std::vector<value> args,
                                       frag_ptr&& before, 
                                       frag_ptr&& body,
                                       frag_ptr&& after) :
  fragment(args),
  before_(std::move(before)),
  body_(std::move(body)),
  after_(std::move(after)),
  num_pointers_(args_.size())
{
  if(args_.empty()) {
    throw std::invalid_argument("Data loop requires at least one argument");
  }

  auto all_params = std::all_of(args_.begin(), args_.end(), [] (auto arg) {
    return arg.value_type == value::type::parameter;
  });

  if(!all_params) { 
    throw std::invalid_argument("Data loop arguments must all be parameter references");
  }
}

data_loop_fragment::data_loop_fragment(std::vector<value> args) :
  data_loop_fragment(args, nullptr, nullptr, nullptr)
{
}

data_loop_fragment::data_loop_fragment(data_loop_fragment const& other) :
  data_loop_fragment(
      other.args_, 
      other.before_ ? other.before_->clone() : nullptr, 
      other.body_ ? other.body_->clone() : nullptr, 
      other.after_ ? other.after_->clone() : nullptr)
{
}

data_loop_fragment::data_loop_fragment(data_loop_fragment&& other) :
  data_loop_fragment(
      std::move(other.args_), std::move(other.before_),
      std::move(other.body_), std::move(other.after_))
{
}

data_loop_fragment& data_loop_fragment::operator=(data_loop_fragment&& other)
{
  args_ = std::move(other.args_);
  before_ = std::move(other.before_);
  body_ = std::move(other.body_);
  after_ = std::move(other.after_);
  return *this;
}

data_loop_fragment& data_loop_fragment::operator=(data_loop_fragment other)
{
  using std::swap;
  swap(*this, other);
  return *this;
}

fragment::frag_ptr data_loop_fragment::clone()
{
  return clone_as(*this);
}

}
