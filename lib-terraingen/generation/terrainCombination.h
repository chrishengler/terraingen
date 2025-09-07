#include <memory>
#include "data_types.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        static Heightmap combineTerrains(std::vector<Heightmap> terrains, std::vector<float> weights);
};

std::unique_ptr<Heightmap> combine(std::unique_ptr<std::vector<Heightmap>> heightmaps, std::unique_ptr<std::vector<float>> weights);