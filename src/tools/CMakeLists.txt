add_executable(detect
  src/detect.cpp)

add_executable(convert
  src/convert.cpp)

target_link_libraries(convert
  ${llvm_libs}
  AccsyntPasses)
