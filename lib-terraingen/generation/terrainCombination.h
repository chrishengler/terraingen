#pragma once
#include <memory>
#include "data_types.h"

class TerrainCombination{
    public:
        TerrainCombination() = default;

        static Heightmap combineTerrains(const std::vector<Heightmap> terrains, const std::vector<float> weights);
};

struct HeightmapHandle;

std::unique_ptr<Heightmap> combine(const std::vector<HeightmapHandle>& heightmaps, const std::vector<float>& weights);