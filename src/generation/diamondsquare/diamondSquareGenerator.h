#pragma once
#include "generator.h"
#include "data_types.h"

class DiamondSquareGenerator : public Generator{
    public:
        DiamondSquareGenerator(unsigned int seed, const Vector2<int> &cell_sizes=Vector2<int>(32,32));
        Heightmap generate(Vector2<int> dimensions) override;

    private:
        int get_required_grid_size(const Vector2<int> &dimensions) const;
        std::vector<int> permutations;
        Vector2<int> cell_sizes;
};
