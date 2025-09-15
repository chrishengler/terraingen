add_subdirectory(stb)
if(NOT MSVC)
    set_source_files_properties(
        stb
        PROPERTIES
        COMPILE_FLAGS "-Wno-conversion -Wno-sign-conversion"
    )
endif()
add_library(lodepng lodepng/lodepng.cpp)