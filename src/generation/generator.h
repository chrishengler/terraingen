#pragma once
#include <vector>

#include "data_types.h"
#include "generatorTypes.h"

class Generator{
    public:
        Generator(unsigned int seed, GeneratorType type);
        virtual Heightmap generate(Vector2<int> dimensions);
        GeneratorType getGeneratorType(){ return type; }

    private:
        unsigned int seed;
        GeneratorType type;
};