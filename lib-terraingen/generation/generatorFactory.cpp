#include <stdexcept>

#include "generator.h"
#include "generatorFactory.h"
#include "generatorTypes.h"

#include "diamondsquare/diamondSquareGenerator.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"

std::unique_ptr<Generator> GeneratorFactory::createGenerator(unsigned int seed, GeneratorType type, Vector2<int> cell_sizes){
    switch(type){
        case GeneratorType::FLAT:
            return std::make_unique<FlatTerrainGenerator>(FlatTerrainGenerator(seed));
        case GeneratorType::PERLIN:
            return std::make_unique<PerlinTerrainGenerator>(PerlinTerrainGenerator(seed, cell_sizes));
        case GeneratorType::DIAMOND_SQUARE:
            return std::make_unique<DiamondSquareGenerator>(DiamondSquareGenerator(seed, cell_sizes));
        default:
            throw std::runtime_error("Unknown generator type");
    }

}