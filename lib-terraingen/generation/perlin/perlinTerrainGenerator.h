#pragma once
#include "generator.h"
#include "data_types.h"
#include "generation/generatorParameters.h"
#include <sys/types.h>

class PerlinTerrainGenerator : public Generator {
    public:
        PerlinTerrainGenerator();
        Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) const override;
        void setParameters(const PerlinParameters& params);
        const PerlinParameters& getParameters() const { return params; }

        std::unique_ptr<std::vector<float>> generate_flat(const uint &x, const uint &y, const uint &seed) const override;
    private:
        double perlin(const Vector2<int> &coordinates, const std::vector<int> &permutations) const;
        double fade(double t) const;
        double gradient(const int hash, const Vector2<double> &coordinates) const;
        // TODO: this isn't going to be thread safe, refactor later
        PerlinParameters params;
};

std::unique_ptr<PerlinTerrainGenerator> new_perlin_generator();