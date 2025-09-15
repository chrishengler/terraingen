#pragma once
#include <memory>
#include "data_types.h"

namespace tg {
    namespace combine {
        struct HeightmapHandle;

        Heightmap combineTerrains(const std::vector<Heightmap> terrains, const std::vector<float> weights);

        std::unique_ptr<Heightmap> combine(const std::vector<HeightmapHandle>& heightmaps, const std::vector<float>& weights);
    }
}
