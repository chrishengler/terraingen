#pragma once
#include "generator.h"
#include "data_types.h"
#include "generation/generatorParameters.h"
#include <sys/types.h>

class PerlinTerrainGenerator : public Generator {
    public:
        PerlinTerrainGenerator();
        Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) override;
        void setParameters(const PerlinParameters& params);
        const PerlinParameters& getParameters() const { return params; }

        std::unique_ptr<Heightmap> generate_as_unique_ptr(const uint &x, const uint &y, const uint &seed) override;
    private:
        double perlin(const Vector2<int> &coordinates);
        double fade(double t);
        double gradient(const int hash, const Vector2<double> &coordinates);
        int retrievePermutation(int permutationIndex);
        std::vector<int> permutations;
        PerlinParameters params;
};

std::unique_ptr<PerlinTerrainGenerator> new_perlin_generator(unsigned int seed);