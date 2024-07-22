cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(TerrainGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(PNG REQUIRED)

add_subdirectory(src)
set(SRCS src/main.cpp)
add_executable(terraingen ${SRCS})

include(${wxWidgets_USE_FILE})
target_include_directories(terraingen PRIVATE ${wxWidgets_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})
target_link_libraries(terraingen ${wxWidgets_LIBRARIES} ${PNG_LIBRARY} terrainlib)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test/test.cpp)
target_include_directories(tests PUBLIC src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain terrainlib)
include(Catch)
include(CTest)
catch_discover_tests(tests)