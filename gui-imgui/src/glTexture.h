#pragma once
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <vector>

#include <GLFW/glfw3.h>

class GLTexture {
public:
    GLuint id = 0;

    ~GLTexture() {
        if (id) glDeleteTextures(1, &id);
    }

    void upload(const std::vector<float>& pixels, int width, int height) {
        if (id) glDeleteTextures(1, &id);
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels.data());
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    operator bool() const { return id != 0; }
};
