add_library(modifierslib
    hydraulic/hydraulicErosionModifier.cpp
    hydraulic/hydraulicErosionModifier.h
)

target_include_directories(modifierslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
