#pragma once
#include "generator.h"
#include "data_types.h"

class PerlinTerrainGenerator : public Generator{
    public:
        PerlinTerrainGenerator(unsigned int seed, const Vector2<unsigned int> &cell_sizes=Vector2<unsigned int>(32,32));
        Heightmap generate(Vector2<unsigned int> dimensions) override;

    private:
        double perlin(const Vector2<int> &coordinates);
        double fade(double t);
        double gradient(const int hash, const Vector2<double> &coordinates);
        std::vector<int> permutations;
        Vector2<unsigned int> cell_sizes;
};