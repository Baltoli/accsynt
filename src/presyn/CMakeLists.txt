add_library(corepresyn
  src/error_function.cpp
  src/optimiser.cpp
  src/parameter.cpp
  src/fragment.cpp
  src/fragment_parse.cpp
  src/sketch.cpp
  src/sketch_context.cpp
  src/candidate.cpp
  src/candidate_operations.cpp
  src/candidate_visitors.cpp
  src/filler.cpp
  src/random_filler.cpp
  src/rule_filler.cpp
  src/rules.cpp
  src/constants.cpp
  src/options.cpp)

add_executable(presyn
  src/main.cpp)

add_executable(presyn-repl
  src/repl.cpp)

add_executable(oracle
  src/oracle_options.cpp
  src/oracle.cpp)

target_link_libraries(corepresyn
  CONAN_PKG::fmt
  CONAN_PKG::taocpp-pegtl
  support
  props
  ${llvm_libs})

target_link_filesystem(corepresyn)

target_link_libraries(presyn
  corepresyn)

target_link_libraries(presyn-repl
  corepresyn)

target_link_libraries(oracle
  corepresyn)

add_executable(presyn_unit
  test/error_function.cpp
  test/fragment.cpp
  test/parsing.cpp
  test/regression.cpp
  test/main.cpp)

target_link_libraries(presyn_unit
  corepresyn
  CONAN_PKG::catch2)

target_include_directories(presyn_unit
  PRIVATE src)

install(
  TARGETS presyn
  DESTINATION ${CMAKE_INSTALL_BINDIR})

add_test(NAME presyn_unit
         COMMAND $<TARGET_FILE:presyn_unit>)
