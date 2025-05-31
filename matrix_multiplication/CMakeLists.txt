cmake_minimum_required (VERSION 3.15)
project (matrix-multiplication)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)
set (CMAKE_CXX_EXTENSIONS FALSE)

add_compile_options (-Wall -Wextra -Wpedantic -march=native)

#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#    add_compile_options(-fno-vectorize)
#elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#    add_compile_options(-fno-tree-vectorize)
#endif()

add_executable (main main.cpp mm0.cpp mm1.cpp mm2.cpp mm3.cpp)

