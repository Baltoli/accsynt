cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_MODULE_PATH 
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/cmake/modules"
)

include(LinkFilesystem)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(AccSynt C CXX)

cmake_policy(SET CMP0025 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(
  "$<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>"
  -Wall -Werror -pedantic 
  -Wno-error=unused-function 
  -Wno-error=unused-variable
  -Wno-error=sign-compare
)

include(TimeTrace)

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-private-field>"
  )
endif()

if(APPLE)
  set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.13/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE "../conanfile.txt"
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

find_package(LLVM 10 REQUIRED CONFIG)

include(ClangTidy)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs
  passes mcjit executionengine option irreader
  asmparser x86asmparser x86codegen asmprinter
  codegen target transformutils
  bitwriter x86desc bitreader
  core x86utils x86info support)

include(GNUInstallDirs)
enable_testing()

add_subdirectory(coverage)
add_subdirectory(passes)
add_subdirectory(props)
add_subdirectory(tools)
add_subdirectory(synth)
add_subdirectory(support)
add_subdirectory(predictor)
add_subdirectory(presyn)
