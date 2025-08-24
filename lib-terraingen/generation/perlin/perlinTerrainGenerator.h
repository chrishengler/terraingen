#pragma once
#include "generator.h"
#include "data_types.h"
#include "generation/generatorParameters.h"

class PerlinTerrainGenerator : public Generator {
    public:
        PerlinTerrainGenerator(unsigned int seed);
        Heightmap generate(const Vec2i &dimensions) override;
        void setParameters(const PerlinParameters& params);
        const PerlinParameters& getParameters() const { return params; }

        std::unique_ptr<Heightmap> generate_as_unique_ptr(const Vec2i &dimensions) override;
    private:
        double perlin(const Vector2<int> &coordinates);
        double fade(double t);
        double gradient(const int hash, const Vector2<double> &coordinates);
        int retrievePermutation(int permutationIndex);
        std::vector<int> permutations;
        PerlinParameters params;
};
