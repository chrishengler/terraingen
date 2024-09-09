cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(TerrainGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(Boost CONFIG REQUIRED )
find_package(PNG REQUIRED)

add_subdirectory(src)
set(SRCS src/main.cpp)
add_executable(terraingen ${SRCS})

include(${wxWidgets_USE_FILE})
target_include_directories(terraingen PRIVATE ${wxWidgets_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})
target_link_libraries(terraingen ${wxWidgets_LIBRARIES} ${PNG_LIBRARY} terrainlib)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test/export.cpp test/generator.cpp test/generatorFactory.cpp test/terrain.cpp)
target_include_directories(tests PUBLIC src {CMAKE_CURRENT_SOURCE_DIR}/test)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain terrainlib generationlib exportlib png)
find_package(Boost CONFIG REQUIRED)
find_package(PNG REQUIRED)
include(Catch)
include(CTest)
catch_discover_tests(tests)
add_custom_target(copy_test_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/test/data ${CMAKE_CURRENT_BINARY_DIR}/data
)
add_dependencies(tests copy_test_data)
