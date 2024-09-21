find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests export.cpp generator.cpp generatorFactory.cpp terrain.cpp integration/perlinExport.cpp)
target_include_directories(tests PUBLIC src ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain terrainlib generationlib exportlib)
include(Catch)
include(CTest)
catch_discover_tests(tests)
add_custom_target(copy_test_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
)
add_dependencies(tests copy_test_data)
