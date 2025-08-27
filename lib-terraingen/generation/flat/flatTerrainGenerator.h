#pragma once
#include "generator.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator : public Generator {
    public:
        FlatTerrainGenerator();
        Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) const override;
        void setParameters(const FlatParameters& params);
        const FlatParameters& getParameters() const { return params; }
    
        std::unique_ptr<std::vector<float>> generate_flat(const uint &x, const uint &y, const uint &seed) const override;
    private:
        FlatParameters params;
};