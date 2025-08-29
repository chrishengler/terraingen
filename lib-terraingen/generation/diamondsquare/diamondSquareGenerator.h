#pragma once
#include "data_types.h"
#include "generatorParameters.h"

class DiamondSquareGenerator{
    public:
        Heightmap generate(const DiamondSquareParameters &params) const;

        std::unique_ptr<std::vector<float>> generate_flat(const DiamondSquareParameters &params) const;
    private:
        int get_required_grid_size(const Vector2<uint32_t> &dimensions) const;
};

std::unique_ptr<DiamondSquareGenerator> new_diamond_square_generator();
