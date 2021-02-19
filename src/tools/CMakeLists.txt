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

add_executable(divine-prep
  src/klee_llvm.cpp
  src/divine.cpp)

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

target_link_libraries(divine-prep
  ${llvm_libs}
  support
  CONAN_PKG::fmt)

install(
  TARGETS detect convert graph-match cyclo instrcount divine-prep
  DESTINATION ${CMAKE_INSTALL_BINDIR})
