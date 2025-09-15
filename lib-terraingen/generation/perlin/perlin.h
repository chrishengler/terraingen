#pragma once
#include "data_types.h"
#include "generation/generatorParameters.h"

namespace tg {
    namespace generate {
        Heightmap generate_perlin(const PerlinParameters &params);

        std::unique_ptr<Heightmap> generate_perlin_unique(const PerlinParameters &params);
        double perlin(const Vector2<int> &coordinates, const std::vector<int> &permutations, const PerlinParameters &params);
        double fade(double t);
        double gradient(const int hash, const Vector2<double> &coordinates);
    }
};