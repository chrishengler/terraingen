#pragma once
#include <vector>

#include "generatorTypes.h"

typedef std::vector<std::vector<unsigned int>> Heightmap;

class Generator{
    public:
        Generator(unsigned int seed, GeneratorType type);
        virtual Heightmap generate(unsigned int size_x, unsigned int size_y);
        GeneratorType getGeneratorType(){ return type; }

    private:
        unsigned int seed;
        GeneratorType type;
};