add_library(corepresyn
  src/options.cpp)

add_executable(presyn
  src/fragment.cpp
  src/fragment_parse.cpp
  src/main.cpp)

target_link_libraries(corepresyn
  CONAN_PKG::fmt
  ${llvm_libs})

target_link_libraries(presyn
  corepresyn)

add_executable(presyn_unit
  test/fragment.cpp
  test/main.cpp)

target_link_libraries(presyn_unit
  corepresyn
  CONAN_PKG::Catch2)

target_include_directories(presyn_unit
  PRIVATE src)

install(
  TARGETS presyn
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_test(NAME presyn_unit
         COMMAND $<TARGET_FILE:presyn_unit>)
