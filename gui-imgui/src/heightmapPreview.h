#pragma once
#include <GLFW/glfw3.h>

#include "glTexture.h"
#include "guiState.h"

class HeightmapPreviewWindow {
public:
    void render(const GuiState& state, const GLTexture& tex);
};