#include "flatTerrainGenerator.h"
#include "generatorParameters.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed, GeneratorType::FLAT)
{}

void FlatTerrainGenerator::setParameters(const FlatParameters& params) {
    this->params = params;
}

Heightmap FlatTerrainGenerator::generate(const Vector2<uint> &dimensions){
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

std::unique_ptr<Heightmap> FlatTerrainGenerator::generate_as_unique_ptr(const uint &x, const uint &y) {
    auto hm = std::make_unique<Heightmap>(generate(Vector2<uint>{x, y}));
    return hm;
}