cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_compile_options(
  -std=c++17
  -Wall -Werror -pedantic 
  -Wno-error=class-memaccess
  -Wno-error=unused-but-set-variable 
  -Wno-error=unused-function 
  -Wno-error=unused-variable
)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE "../conanfile.txt"
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

find_package(LLVM 7 REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader interpreter passes IDLSolver)

include(GNUInstallDirs)
enable_testing()

# add_subdirectory(dist)
add_subdirectory(passes)
add_subdirectory(props)
add_subdirectory(tools)
add_subdirectory(synth)
add_subdirectory(support)

option(BUILD_DOC "Build documentation" OFF)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  if(BUILD_DOC)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doc ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM)
  endif()
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
