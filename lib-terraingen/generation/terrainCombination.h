#include <memory>
#include "data_types.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        static Heightmap combineTerrains(std::vector<Heightmap> terrains, std::vector<float> weights);
        static std::unique_ptr<Heightmap> combine(std::vector<std::unique_ptr<Heightmap>> heightmaps, std::vector<float> weights);
};