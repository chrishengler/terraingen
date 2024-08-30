#include "generator.h"
#include "generatorFactory.h"
#include "generatorTypes.h"

#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"

Generator GeneratorFactory::createGenerator(GeneratorType type){
    switch(type){
        case GeneratorType::FLAT:
            return FlatTerrainGenerator(4);
        case GeneratorType::PERLIN:
            return PerlinTerrainGenerator(4);
    }
}