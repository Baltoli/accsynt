add_executable(synth
  src/synth.cpp)

target_link_libraries(synth
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  props)

install(
  TARGETS synth
  DESTINATION ${CMAKE_INSTALL_BINDIR})
