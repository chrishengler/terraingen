#pragma once
#include "generator.h"
#include "generatorTypes.h"

class GeneratorFactory {
    public:
        static std::unique_ptr<Generator> createGenerator(unsigned int seed, GeneratorType type);
};