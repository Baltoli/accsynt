add_executable(asyn
  src/main.cpp
)

target_link_libraries(asyn
  synth
  dist
)
