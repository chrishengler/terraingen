#pragma once
#include "generator.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator : public Generator {
    public:
        FlatTerrainGenerator(unsigned int seed);
        Heightmap generate(Vector2<int> dimensions) override;
        void setParameters(const FlatParameters& params);
        const FlatParameters& getParameters() const { return params; }
    
    private:
        FlatParameters params;
};