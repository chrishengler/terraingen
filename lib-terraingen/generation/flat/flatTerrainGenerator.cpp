#include <cstdint>
#include "flatTerrainGenerator.h"
#include "generatorParameters.h"

Heightmap FlatTerrainGenerator::generate(const FlatParameters &params) const {
    Heightmap heightmap;   
    Vector2<uint32_t> dimensions{params.cols, params.rows};
    for(uint32_t col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(uint32_t row=0; row<dimensions.y; row++){
            column[row] = params.terrainHeight;
        }
        heightmap.push_back(column);
    }
    return heightmap;
}

std::unique_ptr<std::vector<float>> FlatTerrainGenerator::generate_flat(const FlatParameters &params) const {
    auto hm = std::make_unique<Heightmap>(generate(params));
    return flattenHeightmap(*hm);
}