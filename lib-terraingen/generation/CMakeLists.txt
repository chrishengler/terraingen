add_library(generationlib terrainCombination.cpp perlin/perlin.cpp diamondsquare/diamondSquare.cpp)
target_include_directories(generationlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIRECTORY}../)