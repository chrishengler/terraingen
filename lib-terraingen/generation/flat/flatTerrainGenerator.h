#pragma once
#include "generator.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator : public Generator {
    public:
        FlatTerrainGenerator(unsigned int seed);
        Heightmap generate(const Vector2<uint> &dimensions) override;
        void setParameters(const FlatParameters& params);
        const FlatParameters& getParameters() const { return params; }
    
        std::unique_ptr<Heightmap> generate_as_unique_ptr(const uint &x, const uint &y) override;
    private:
        FlatParameters params;
};