#pragma once
#include "generator.h"

class PerlinTerrainGenerator : public Generator{
    public:
        PerlinTerrainGenerator(unsigned int seed);
        Heightmap generate(unsigned int size_x, unsigned int size_y) override;
};