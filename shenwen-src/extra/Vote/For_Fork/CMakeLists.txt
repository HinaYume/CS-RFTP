set(LLVM_LINK_COMPONENTS support)



add_clang_executable(For_Fork

  for_fork.cpp

  )

target_link_libraries(For_Fork

  clangTooling

  clangBasic

  clangASTMatchers

  )