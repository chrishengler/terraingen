cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(TerrainGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
