#include "terrain/terrain.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        static Terrain combineTerrains(std::vector<Terrain> terrains, std::vector<float> weights);
};