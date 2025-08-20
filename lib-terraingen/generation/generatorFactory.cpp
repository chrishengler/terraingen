#include <stdexcept>

#include "generator.h"
#include "generatorFactory.h"
#include "generatorTypes.h"

#include "diamondsquare/diamondSquareGenerator.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"

std::unique_ptr<Generator> GeneratorFactory::createGenerator(unsigned int seed, GeneratorType type) {
    switch(type) {
        case GeneratorType::FLAT: {
            auto generator = std::make_unique<FlatTerrainGenerator>(seed);
            return generator;
        }
        case GeneratorType::PERLIN: {
            auto generator = std::make_unique<PerlinTerrainGenerator>(seed);
            return generator;
        }
        case GeneratorType::DIAMOND_SQUARE:
            return std::make_unique<DiamondSquareGenerator>(seed);
        default:
            throw std::runtime_error("Unknown generator type");
    }

}