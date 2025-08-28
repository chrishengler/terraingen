#include "flatTerrainGenerator.h"
#include "generatorParameters.h"

Heightmap FlatTerrainGenerator::generate(const FlatParameters &params) const {
    Heightmap heightmap;   
    Vector2<uint> dimensions{params.cols, params.rows};
    for(uint col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(uint row=0; row<dimensions.y; row++){
            column[row] = params.terrainHeight;
        }
        heightmap.push_back(column);
    }
    return heightmap;
}

std::unique_ptr<std::vector<float>> FlatTerrainGenerator::generate_flat(const FlatParameters &params) const {
    auto hm = generate(params);
    return std::make_unique<std::vector<float>>(flattenHeightmap(hm));
}