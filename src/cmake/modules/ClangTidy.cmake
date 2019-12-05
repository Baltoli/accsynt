include(ListJoin)

find_program(
  CLANG_TIDY_EXE
  "clang-tidy"
  HINTS "${LLVM_INSTALL_PREFIX}/bin"
)

set(CLANG_TIDY_CHECKS_LIST
  "-*"
  "bugprone-*"
  "-bugprone-exception-escape"
  "-bugprone-macro-parentheses"
  "-bugprone-narrowing-conversions"
  "-bugprone-sizeof-expression"
)
JOIN("${CLANG_TIDY_CHECKS_LIST}" "," CLANG_TIDY_CHECKS)

if(CLANG_TIDY_EXE)
  set(CLANG_TIDY 
    "${CLANG_TIDY_EXE}"
    "-checks=${CLANG_TIDY_CHECKS}"
  )

  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
else()
  message(WARNING "No clang-tidy found")
endif()
