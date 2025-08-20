#pragma once
#include "generator.h"
#include "data_types.h"
#include "generation/generatorParameters.h"

class PerlinTerrainGenerator : public Generator {
    public:
        PerlinTerrainGenerator(unsigned int seed);
        Heightmap generate(Vector2<int> dimensions) override;
        void setParameters(const PerlinParameters& params);
        const PerlinParameters& getParameters() const { return params; }

    private:
        double perlin(const Vector2<int> &coordinates);
        double fade(double t);
        double gradient(const int hash, const Vector2<double> &coordinates);
        int retrievePermutation(int permutationIndex);
        std::vector<int> permutations;
        PerlinParameters params;
};