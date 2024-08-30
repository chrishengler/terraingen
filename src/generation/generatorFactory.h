#pragma once
#include "generator.h"
#include "generatorTypes.h"

class GeneratorFactory{
    public:
        static Generator createGenerator(GeneratorType type);
};