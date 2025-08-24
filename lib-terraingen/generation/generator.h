#pragma once
#include <memory> 

#include "data_types.h"
#include "generatorTypes.h"

class Generator {
    public:
        Generator(unsigned int seed, GeneratorType type);
        virtual ~Generator() = default;
        virtual Heightmap generate(const Vector2<uint> &dimensions);
        GeneratorType getGeneratorType(){ return type; }

        // for rust interface
        virtual std::unique_ptr<Heightmap> generate_as_unique_ptr(const uint &x, const uint &y);
    protected:
        unsigned int seed;
    private:
        GeneratorType type;
};