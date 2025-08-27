#pragma once

#include "data_types.h"
#include "generatorTypes.h"

class Generator {
    public:
        Generator(GeneratorType type);
        virtual ~Generator() = default;
        virtual Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) const;
        GeneratorType getGeneratorType(){ return type; }

        // for rust interface
        virtual std::unique_ptr<std::vector<float>> generate_flat(const uint &x, const uint &y, const uint &seed) const;
    protected:
        unsigned int seed;
    private:
        GeneratorType type;
};