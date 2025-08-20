#pragma once
#include "data_types.h"
#include "generatorTypes.h"
#include "generation/generatorParameters.h"

class Generator {
    public:
        Generator(unsigned int seed, GeneratorType type);
        virtual ~Generator() = default;
        virtual Heightmap generate(Vector2<int> dimensions);
        GeneratorType getGeneratorType(){ return type; }
        virtual void setParameters(const GeneratorParameters& params) = 0;

    protected:
        unsigned int seed;
    private:
        GeneratorType type;
};