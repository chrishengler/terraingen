#pragma once
#include <cstdint>
#include <memory>

struct PerlinParameters{
    uint32_t cols;
    uint32_t rows;
    int32_t seed;
    float scale = 1.0f;
    int32_t cellSize = 32;
};

inline std::unique_ptr<PerlinParameters> buildPerlinParameters(uint32_t cols, uint32_t rows, int32_t seed, float scale, int32_t cell_size){
    return std::make_unique<PerlinParameters>(PerlinParameters{cols, rows, seed, scale, cell_size});
}

struct DiamondSquareParameters{
    uint32_t cols;
    uint32_t rows;
    int32_t seed;
    float roughness = 1.0;
};

inline std::unique_ptr<DiamondSquareParameters> buildDiamondSquareParameters(uint32_t cols, uint32_t rows, int32_t seed, float roughness){
    return std::make_unique<DiamondSquareParameters>(DiamondSquareParameters{cols, rows, seed, roughness});
}
