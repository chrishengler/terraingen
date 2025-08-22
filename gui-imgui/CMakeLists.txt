cmake_minimum_required(VERSION 3.16)

project(gui-imgui)

find_package(OpenGL REQUIRED)

# GLFW (windowing/input)
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.0   # latest stable as of now
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw)


add_executable(gui-imgui
    src/main.cpp
    src/terrainControls.cpp
    src/heightmapPreview.cpp
)

target_include_directories(gui-imgui PUBLIC
    lib-terraingen
)
target_link_libraries(gui-imgui
    PRIVATE
        imgui
        glfw
        lib-terraingen
        generationlib
        exportlib
        OpenGL::GL
)

