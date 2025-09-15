#pragma once
#include "data_types.h"
#include "generatorParameters.h"

namespace tg {
    namespace generate {
        Heightmap generate_ds(const DiamondSquareParameters &params);

        std::unique_ptr<Heightmap> generate_ds_unique(const DiamondSquareParameters &params);
    }
}
