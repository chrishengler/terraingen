#pragma once
#include <cstdint>
#include <memory>

struct PerlinParameters{
    float scale = 1.0f;
    int32_t cellSize = 32;
};

inline std::unique_ptr<PerlinParameters> buildPerlinParameters(float scale, int32_t cell_size){
    return std::make_unique<PerlinParameters>(PerlinParameters{scale, cell_size});
}

struct FlatParameters{
    float height = 0.5;
};

struct DiamondSquareParameters{
    float roughness = 1.0;
};

inline std::unique_ptr<DiamondSquareParameters> buildDiamondSquareParameters(float roughness){
    return std::make_unique<DiamondSquareParameters>(DiamondSquareParameters{roughness});
}
