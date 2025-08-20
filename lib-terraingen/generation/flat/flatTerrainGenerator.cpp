#include "flatTerrainGenerator.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed, GeneratorType::FLAT)
{}

void FlatTerrainGenerator::setParameters(const GeneratorParameters& params) {
    if (auto flatParams = dynamic_cast<const FlatParameters*>(&params)) {
        setParameters(*flatParams);
    }
}

void FlatTerrainGenerator::setParameters(const FlatParameters& params) {
    this->params = params;
}

Heightmap FlatTerrainGenerator::generate(Vector2<int> dimensions){
    Heightmap heightmap;   
    for(int col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(int row=0; row<dimensions.y; row++){
            column[row] = params.height;
        }
        heightmap.push_back(column);
    }
    return heightmap;
}