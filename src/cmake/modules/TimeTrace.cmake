option(CLANG_TIME_TRACE "Enable clang profiling." OFF)

if(CLANG_TIME_TRACE)
  add_compile_options(-ftime-trace)
endif()
