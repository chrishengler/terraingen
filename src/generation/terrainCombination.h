#include "terrain/terrain.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        Terrain combineTerrains(std::vector<Terrain> terrains, std::vector<float> weights);
};