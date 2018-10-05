add_executable(synth
  src/synth.cpp)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})
