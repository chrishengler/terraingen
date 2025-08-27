#pragma once
#include "data_types.h"
#include "generation/generatorParameters.h"

class FlatTerrainGenerator{
    public:
        Heightmap generate(const FlatParameters &params) const;
    
        std::unique_ptr<std::vector<float>> generate_flat(const FlatParameters &params) const;
    private:
        FlatParameters params;
};