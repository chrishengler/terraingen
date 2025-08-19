// --------------------------
// Silence OpenGL deprecation warnings on macOS
// --------------------------
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "generatorFactory.h"
#include "generator.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <valarray>
#include <cstdint>

struct GuiState {
    GeneratorType selectedType = GeneratorType::PERLIN;
    Vector2<int> gridSize{64, 64};
    unsigned int seed = 0;
    bool generateRequested = false;
    GLuint heightmapTexture = 0;
};

// Flatten Heightmap to contiguous float array for OpenGL
std::vector<float> flattenHeightmap(const Heightmap& hm) {
    std::vector<float> pixels;
    size_t rows = hm.size();
    size_t cols = hm.empty() ? 0 : hm[0].size();
    pixels.reserve(rows * cols);
    for (const auto& row : hm)
        for (double v : row)
            pixels.push_back(static_cast<float>(v));
    return pixels;
}

int main() {
    GuiState guiState;

    // --------------------------
    // Initialize GLFW
    // --------------------------
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
    if (!window) { std::cerr << "Failed to create GLFW window\n"; glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // --------------------------
    // Setup Dear ImGui context
    // --------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

#ifdef __APPLE__
    const char* glsl_version = "#version 150";
#else
    const char* glsl_version = "#version 130";
#endif

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) { std::cerr << "Failed to init ImGui GLFW\n"; return 1; }
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) { std::cerr << "Failed to init ImGui OpenGL3\n"; return 1; }

    // --------------------------
    // Main loop
    // --------------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // ----- Start a new ImGui frame -----
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ----- Terrain Generator controls -----
        ImGui::Begin("Terrain Generator");

        const char* generatorNames[] = { "Flat", "Perlin", "Diamond-Square" };
        int typeIndex = static_cast<int>(guiState.selectedType);
        if (ImGui::Combo("Generator Type", &typeIndex, generatorNames, IM_ARRAYSIZE(generatorNames)))
            guiState.selectedType = static_cast<GeneratorType>(typeIndex);

        ImGui::InputInt("Width", &guiState.gridSize.x);
        ImGui::InputInt("Height", &guiState.gridSize.y);
        ImGui::InputInt("Seed", reinterpret_cast<int*>(&guiState.seed));

        if (ImGui::Button("Generate"))
            guiState.generateRequested = true;

        ImGui::End();

        // ----- Run generator if requested -----
        if (guiState.generateRequested) {
            guiState.generateRequested = false;

            auto generator = GeneratorFactory::createGenerator(
                guiState.seed, guiState.selectedType, guiState.gridSize
            );

            Heightmap hm = generator->generate(guiState.gridSize);
            auto pixels = flattenHeightmap(hm);

            if (guiState.heightmapTexture != 0)
                glDeleteTextures(1, &guiState.heightmapTexture);

            glGenTextures(1, &guiState.heightmapTexture);
            glBindTexture(GL_TEXTURE_2D, guiState.heightmapTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, guiState.gridSize.x, guiState.gridSize.y,
                         0, GL_RED, GL_FLOAT, pixels.data());
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        // ----- Heightmap preview -----
        if (guiState.heightmapTexture != 0) {
            ImGui::Begin("Heightmap Preview");
            ImGui::Text("Generated Heightmap:");
            ImGui::Image((void*)(intptr_t)guiState.heightmapTexture,
                         ImVec2(guiState.gridSize.x, guiState.gridSize.y));
            ImGui::End();
        }

        // ----- Render -----
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // --------------------------
    // Cleanup
    // --------------------------
    if (guiState.heightmapTexture != 0)
        glDeleteTextures(1, &guiState.heightmapTexture);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
