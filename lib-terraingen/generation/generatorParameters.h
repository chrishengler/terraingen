#pragma once
#include "data_types.h"

struct GeneratorParameters {
    virtual ~GeneratorParameters() = default;
    Vector2<int> gridSize = { 256, 256 }; // Default grid size

    GeneratorParameters() = default;
    explicit GeneratorParameters(Vector2<int> gs) : gridSize(gs) {}
};

struct PerlinParameters: public GeneratorParameters {
    float scale = 1.0f;
    int cellSize = 32;


    PerlinParameters(
        Vector2<int> gridSize = {256, 256},
        float scale = 1.0f,
        int cellSize = 32
    )
        : GeneratorParameters{gridSize}, scale(scale), cellSize(cellSize) {}
};

struct FlatParameters: public GeneratorParameters {
    float height = 0.5;

    FlatParameters(
        Vector2<int> gridSize = {256, 256},
        float height = 0.5
    )
        : GeneratorParameters{gridSize}, height(height) {}
};

struct DiamondSquareParameters: public GeneratorParameters {
    double roughness = 1.0;

    DiamondSquareParameters(
        Vector2<int> gridSize = {256, 256},
        double roughness = 1.0
    )
        : GeneratorParameters{gridSize}, roughness(roughness) {}
};
