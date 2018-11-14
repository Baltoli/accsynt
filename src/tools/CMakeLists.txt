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

target_link_libraries(convert
  CONAN_PKG::fmt
  ${llvm_libs}
  AccsyntPasses)

target_link_libraries(detect
  CONAN_PKG::fmt
  -Wl,--whole-archive ${llvm_libs} -Wl,--no-whole-archive)

target_link_libraries(graph-match
  ${llvm_libs})

install(
  TARGETS detect convert graph-match
  DESTINATION ${CMAKE_INSTALL_BINDIR})
