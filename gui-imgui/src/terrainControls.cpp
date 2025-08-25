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

  int tmp_x = static_cast<int>(state.gridSize.x);
  int tmp_y = static_cast<int>(state.gridSize.y);
  if(ImGui::InputInt("Width", &tmp_x))
  {
    if(tmp_x < 0){
      tmp_x = 0;
    }
    state.gridSize.x = static_cast<uint>(tmp_x);
  }
  ImGui::InputInt("Height", &tmp_y);
  {
    if(tmp_y < 0){
      tmp_y = 0;
    }
    state.gridSize.y = static_cast<uint>(tmp_y);
  }
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
  switch (state.selectedType) {
    case GeneratorType::DIAMOND_SQUARE: {
      ImGui::SliderFloat("Roughness", &state.diamondSquareParams.roughness, 0.1f,
                        2.0f, "%.2f");
    } break;
    case GeneratorType::PERLIN: {
      ImGui::SliderFloat("Scale", &state.perlinParams.scale, 0.1f, 10.0f,
                         "%.2f");
      ImGui::InputInt("Cell Size", &state.perlinParams.cellSize);
      // Clamp cell size to reasonable values
      state.perlinParams.cellSize =
          std::max(1, std::min(256, state.perlinParams.cellSize));
    } break;
    case GeneratorType::FLAT: {
      ImGui::InputFloat("Terrain Height", &state.flatParams.height, 0.1, 1.0,
                        "%.1f");
    } break;
    default:
      break;
    }

  if (ImGui::Button("Generate"))
    state.generateRequested = true;

  ImGui::End();
}
