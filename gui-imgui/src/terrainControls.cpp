#include <random>

#include "imgui.h"
#include "terrainControls.h"

void TerrainControlsWindow::render(GuiState &state) {
  ImGui::Begin("Terrain Generator");

  const char *generatorNames[] = {"Flat", "Perlin", "Diamond-Square"};
  int typeIndex = static_cast<int>(state.selectedType);
  if (ImGui::Combo("Generator Type", &typeIndex, generatorNames,
                   IM_ARRAYSIZE(generatorNames)))
    state.selectedType = static_cast<GeneratorType>(typeIndex);

  ImGui::InputInt("Width", &state.gridSize.x);
  ImGui::InputInt("Height", &state.gridSize.y);
  ImGui::InputInt("Seed", reinterpret_cast<int *>(&state.seed));
  if (ImGui::Button("Random Seed")) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 0x7fffffff);
    state.seed = dist(gen);
  }
  ImGui::SameLine();
  if (ImGui::Button("New Seed and autogenerate")) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 0x7fffffff);
    state.seed = dist(gen);
    state.generateRequested = true;
  }

  // Show generator-specific parameters
  if (state.selectedType == GeneratorType::PERLIN) {
    ImGui::SliderFloat("Scale", &state.perlinParams.scale, 0.1f, 10.0f, "%.2f");
    ImGui::InputInt("Cell Size", &state.perlinParams.cellSize);
    // Clamp cell size to reasonable values
    state.perlinParams.cellSize =
        std::max(1, std::min(256, state.perlinParams.cellSize));
  } else if (state.selectedType == GeneratorType::FLAT) {
    ImGui::InputFloat("Terrain Height", &state.flatParams.height, 0.1, 1.0,
                      "%.1f");
  }

  if (ImGui::Button("Generate"))
    state.generateRequested = true;

  ImGui::End();
}
