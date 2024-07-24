add_library(generationlib generator.cpp flat/flatTerrainGenerator.cpp)
target_include_directories(generationlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})