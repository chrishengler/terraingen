#pragma once
#include <cstdint>
#include <memory>

struct GeneratorParameters {
    uint32_t width;
    uint32_t height;
    int32_t seed;
};

struct PerlinParameters: GeneratorParameters{
    float scale = 1.0f;
    int32_t cellSize = 32;
};

inline std::unique_ptr<PerlinParameters> buildPerlinParameters(uint32_t width, uint32_t height, int32_t seed, float scale, int32_t cell_size){
    return std::make_unique<PerlinParameters>(PerlinParameters{width, height, seed, scale, cell_size});
}

struct FlatParameters: GeneratorParameters{
    float terrainHeight = 0.5;
};

struct DiamondSquareParameters: GeneratorParameters{
    float roughness = 1.0;
};

inline std::unique_ptr<DiamondSquareParameters> buildDiamondSquareParameters(uint32_t width, uint32_t height, int32_t seed, float roughness){
    return std::make_unique<DiamondSquareParameters>(DiamondSquareParameters{width, height, seed, roughness});
}
