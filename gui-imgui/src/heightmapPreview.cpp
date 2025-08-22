#include <cstdint>

#include "glTexture.h"
#include "guiState.h"
#include "heightmapPreview.h"
#include "imgui.h"

void HeightmapPreviewWindow::render(const GuiState &state,
                                    const GLTexture &tex) {
  if (!tex)
    return;

  ImGui::Begin("Heightmap Preview");

  // Get available content region size (space inside the window)
  ImVec2 availSize = ImGui::GetContentRegionAvail();

  // Compute aspect ratio based on terrain grid
  float aspect = static_cast<float>(state.gridSize.x) /
                 static_cast<float>(state.gridSize.y);

  ImVec2 imageSize;
  if (availSize.x / availSize.y > aspect) {
    // Window is wider than terrain; fit to height
    imageSize.y = availSize.y;
    imageSize.x = imageSize.y * aspect;
  } else {
    // Window is taller than terrain; fit to width
    imageSize.x = availSize.x;
    imageSize.y = imageSize.x / aspect;
  }

  ImGui::Text("Generated Heightmap:");
  ImGui::Image((void *)(intptr_t)tex.id, imageSize);

  ImGui::End();
}