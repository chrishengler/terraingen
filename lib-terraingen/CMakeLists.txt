add_subdirectory(generation)
add_subdirectory(export)
add_library(lib-terraingen terrain/terrain.cpp)
target_include_directories(lib-terraingen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})