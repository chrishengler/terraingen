if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
add_library(stb_image stb_image_write.h stb_image.h stbi.cpp)