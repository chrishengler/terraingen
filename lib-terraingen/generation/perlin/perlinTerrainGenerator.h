#pragma once
#include "data_types.h"
#include "generation/generatorParameters.h"

class PerlinTerrainGenerator{
    public:
        Heightmap generate(const PerlinParameters &params) const;

        std::unique_ptr<Heightmap> generate_unique(const PerlinParameters &params) const;
    private:
        double perlin(const Vector2<int> &coordinates, const std::vector<int> &permutations, const PerlinParameters &params) const;
        double fade(double t) const;
        double gradient(const int hash, const Vector2<double> &coordinates) const;
};

std::unique_ptr<PerlinTerrainGenerator> new_perlin_generator();