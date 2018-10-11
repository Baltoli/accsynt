#pragma once

#include "call_builder.h"

#include <props/props.h>

namespace synth {

/*
 * The initial generator implementation is just going to randomly generate the
 * values for the signature. However, the interface will accept a property_set
 * rather than just a signature so that the properties can be used during the
 * generation process (i.e. respecting fixed values, zeroing outputs etc).
 */
class generator {
public:
  generator(props::property_set ps);

  virtual void generate(call_builder& builder);

protected:
  props::property_set properties_;
};

}
