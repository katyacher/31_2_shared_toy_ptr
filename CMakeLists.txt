cmake_minimum_required(VERSION 3.8.0)
project(31_2_shared_toy_ptr VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(31_2_shared_toy_ptr main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
