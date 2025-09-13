add_library(exportlib imageExporter.cpp)
target_include_directories(exportlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIRECTORY}../)
include(CMakePrintHelpers)