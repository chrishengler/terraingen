#include "flatTerrainGenerator.h"
#include "generatorParameters.h"

FlatTerrainGenerator::FlatTerrainGenerator()
    : Generator(GeneratorType::FLAT)
{}

void FlatTerrainGenerator::setParameters(const FlatParameters& params) {
    this->params = params;
}

Heightmap FlatTerrainGenerator::generate(const Vector2<uint> &dimensions, const uint&) const {
    Heightmap heightmap;   
    for(uint col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(uint row=0; row<dimensions.y; row++){
            column[row] = params.height;
        }
        heightmap.push_back(column);
    }
    return heightmap;
}

std::unique_ptr<std::vector<float>> FlatTerrainGenerator::generate_flat(const uint &x, const uint &y, const uint &seed) const {
    auto hm = generate(Vector2<uint>{x, y}, seed);
    return std::make_unique<std::vector<float>>(flattenHeightmap(hm));
}