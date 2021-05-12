add_executable(detect
  src/detect.cpp)

add_executable(convert
  src/convert.cpp)

add_executable(graph-match
  src/node.cpp
  src/graph_match.cpp
  src/load_graph.cpp
  src/algorithm.cpp
  src/graph.cpp
  src/match.cpp)

add_executable(cyclo
  src/cyclo.cpp)

add_executable(instrcount
  src/count.cpp)

add_executable(props-filter
  src/filter.cpp)

add_executable(norm
  src/norm.cpp)

add_executable(sanity-check
  src/sanity-check.cpp)

add_executable(instrument
  src/print_opcode.cpp
  src/instrument.cpp)

target_link_libraries(convert
  CONAN_PKG::fmt
  ${llvm_libs}
  AccsyntPasses_static)

if(APPLE)
  target_link_libraries(detect
    CONAN_PKG::fmt
    ${llvm_libs})
else()
  target_link_libraries(detect
    CONAN_PKG::fmt
    -Wl,--whole-archive ${llvm_libs} -Wl,--no-whole-archive)
endif()

target_link_libraries(graph-match
  support
  ${llvm_libs})

target_link_libraries(cyclo
  ${llvm_libs}
  AccsyntPasses_static)

target_link_libraries(instrcount
  ${llvm_libs}
  AccsyntPasses_static)

target_link_libraries(props-filter
  CONAN_PKG::fmt
  ${llvm_libs}
  props
  support)

target_link_filesystem(props-filter)

target_link_libraries(instrument
  CONAN_PKG::fmt
  ${llvm_libs}
  support)

target_link_filesystem(instrument)

target_link_libraries(norm
  CONAN_PKG::fmt
  ${llvm_libs}
  support)

target_link_filesystem(norm)

target_link_libraries(sanity-check
  CONAN_PKG::fmt
  ${llvm_libs}
  props
  support)

target_link_filesystem(sanity-check)

install(
  TARGETS detect convert graph-match cyclo instrcount norm
  DESTINATION ${CMAKE_INSTALL_BINDIR})
