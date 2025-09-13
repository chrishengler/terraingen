add_subdirectory(stb)
set_source_files_properties(
    stb
    PROPERTIES
    COMPILE_FLAGS "-Wno-conversion -Wno-sign-conversion"
)