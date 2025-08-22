#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "flat/flatTerrainGenerator.h"
#include "generatorFactory.h"
#include "guiState.h"
#include "perlin/perlinTerrainGenerator.h"
#include "terrainControls.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <cstdint>
#include <iostream>



// --------------------------
// OpenGL texture helper
// --------------------------
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

// --------------------------
// Utility to flatten Heightmap
// --------------------------
std::vector<float> flattenHeightmap(const Heightmap& hm) {
    std::vector<float> pixels;
    size_t rows = hm.size();
    size_t cols = hm.empty() ? 0 : hm[0].size();
    pixels.reserve(rows * cols);
    for (const auto& row : hm)
      for (double v : row) {
        float f = static_cast<float>(v);
        pixels.push_back(f);
        pixels.push_back(f);
        pixels.push_back(f);
      }
    return pixels;
}


// --------------------------
// Heightmap preview window
// --------------------------
class HeightmapPreviewWindow {
public:
    void render(const GuiState& state, const GLTexture& tex) {
        if (!tex) return;

        ImGui::Begin("Heightmap Preview");

        // Get available content region size (space inside the window)
        ImVec2 availSize = ImGui::GetContentRegionAvail();

        // Compute aspect ratio based on terrain grid
        float aspect = static_cast<float>(state.gridSize.x) / static_cast<float>(state.gridSize.y);

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
        ImGui::Image((void*)(intptr_t)tex.id, imageSize);

        ImGui::End();
    }
};

// --------------------------
// Main
// --------------------------
int main() {
    // Initialize GLFW
    if (!glfwInit()) return 1;
#if defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Terrain Generator", nullptr, nullptr);
    if (!window) { std::cerr << "Failed to create window\n"; glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

#ifdef __APPLE__
    const char* glsl_version = "#version 150";
#else
    const char* glsl_version = "#version 130";
#endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // GUI modules and state
    GuiState guiState;
    GLTexture heightmapTexture;
    TerrainControlsWindow controlsWindow;
    HeightmapPreviewWindow previewWindow;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render GUI windows
        controlsWindow.render(guiState);

        // Run terrain generator if requested
        if (guiState.generateRequested) {
            guiState.generateRequested = false;

            auto generator = GeneratorFactory::createGenerator(guiState.seed, guiState.selectedType);
            
            // Configure generator-specific parameters
            if (auto perlinGen = dynamic_cast<PerlinTerrainGenerator*>(generator.get())) {
                perlinGen->setParameters(guiState.perlinParams);
            }
            else if (auto flatGen = dynamic_cast<FlatTerrainGenerator*>(generator.get())) {
                flatGen->setParameters(guiState.flatParams);
            }

            Heightmap hm = generator->generate(guiState.gridSize);
            auto pixels = flattenHeightmap(hm);
            heightmapTexture.upload(pixels, guiState.gridSize.x, guiState.gridSize.y);
        }

        previewWindow.render(guiState, heightmapTexture);

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
