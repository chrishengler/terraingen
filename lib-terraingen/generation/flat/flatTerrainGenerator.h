#pragma once
#include "generator.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator : public Generator {
    public:
        FlatTerrainGenerator(unsigned int seed);
        Heightmap generate(const Vec2i &dimensions) override;
        void setParameters(const FlatParameters& params);
        const FlatParameters& getParameters() const { return params; }
    
        std::unique_ptr<Heightmap> generate_as_unique_ptr(const Vec2i &dimensions) override;
    private:
        FlatParameters params;
};