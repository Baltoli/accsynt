project(libsynth VERSION 0.1 LANGUAGES CXX)

add_library(synth
  src/oracle.cpp
  src/generator.cpp
)

target_include_directories(synth PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(synth
  ${llvm_libs}
)

install(TARGETS synth EXPORT SynthConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT SynthConfig DESTINATION share/Synth/cmake)

export(TARGETS synth FILE SynthConfig.cmake)
