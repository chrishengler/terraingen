add_subdirectory(generation)
add_subdirectory(export)
add_library(terrainlib terrain/terrain.cpp)
target_include_directories(terrainlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})