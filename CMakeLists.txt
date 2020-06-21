cmake_minimum_required(VERSION 3.0.0)
project(IntMatrix VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Matrix test_partB.cpp Auxiliaries.cpp Auxiliaries.h Matrix.h complex/complex.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
