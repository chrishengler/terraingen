#pragma once
#include "generator.h"
#include "generatorTypes.h"

class GeneratorFactory{
    public:
        static Generator createGenerator(unsigned int seed, GeneratorType type, Vector2<int> cell_sizes = Vector2<int>(16,16));
};