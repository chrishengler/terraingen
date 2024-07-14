cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(TerrainGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(CImg-3.4.0 REQUIRED)

set(SRCS src/main.cpp)
add_executable(terraingen ${SRCS})

include(${wxWidgets_USE_FILE})
target_include_directories(terraingen PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(terraingen ${wxWidgets_LIBRARIES})
