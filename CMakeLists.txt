cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(TerrainGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(lib-terraingen)
if(NOT MSVC)
    add_compile_options(-Wconversion -Wsign-conversion)
endif()

enable_testing()
add_subdirectory(test)
