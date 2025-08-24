#pragma once
#include <memory> 

#include "data_types.h"
#include "generatorTypes.h"

class Generator {
    public:
        Generator(unsigned int seed, GeneratorType type);
        virtual ~Generator() = default;
        virtual Heightmap generate(const Vec2i &dimensions);
        GeneratorType getGeneratorType(){ return type; }

        // for rust interface
        virtual std::unique_ptr<Heightmap> generate_as_unique_ptr(const Vec2i &dimensions);
    protected:
        unsigned int seed;
    private:
        GeneratorType type;
};