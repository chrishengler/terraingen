#include "data_types.h"
#include "terrain/terrain.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        Terrain combineTerrains(std::vector<Terrain> terrains, std::vector<float> weights);
};