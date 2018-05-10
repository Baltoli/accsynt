add_library(AccsyntPasses MODULE
  src/clean.cpp
)

set_target_properties(AccsyntPasses PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
