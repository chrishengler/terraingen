#include "generator.h"

class FlatTerrainGenerator : Generator{
    public:
        FlatTerrainGenerator(unsigned int seed);
        Heightmap generate(unsigned int size_x, unsigned int size_y) override;
};