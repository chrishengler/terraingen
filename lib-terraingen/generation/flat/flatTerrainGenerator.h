#pragma once
#include "generator.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator : public Generator {
    public:
        FlatTerrainGenerator();
        Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) override;
        void setParameters(const FlatParameters& params);
        const FlatParameters& getParameters() const { return params; }
    
        std::unique_ptr<Heightmap> generate(const uint &x, const uint &y, const uint &seed) override;
    private:
        FlatParameters params;
};