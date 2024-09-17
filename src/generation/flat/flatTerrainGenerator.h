#pragma once
#include "generator.h"

class FlatTerrainGenerator : public Generator{
    public:
        FlatTerrainGenerator(unsigned int seed);
        Heightmap generate(Vector2<int> dimensions) override;
};