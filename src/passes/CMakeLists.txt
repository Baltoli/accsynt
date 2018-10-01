add_library(AccsyntPasses MODULE
  src/clean.cpp
  src/namer.cpp
  src/to_idl.cpp
)

set_target_properties(AccsyntPasses PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
