#include "modifierControls.h"
#include "imgui.h"

void ModifierControlsWindow::render(GuiState& state) {
    ImGui::Begin("Terrain Modifiers");

    if (ImGui::Button("Apply Hydraulic Erosion")) {
        state.modifyRequested = true;
    }

    ImGui::End();
}
