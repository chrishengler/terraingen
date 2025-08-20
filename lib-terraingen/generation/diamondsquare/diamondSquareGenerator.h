#pragma once
#include "generator.h"
#include "data_types.h"

class DiamondSquareGenerator : public Generator{
    public:
        DiamondSquareGenerator(unsigned int seed);
        Heightmap generate(Vector2<int> dimensions) override;
        void setParameters(const GeneratorParameters& params) override;

    private:
        int get_required_grid_size(const Vector2<int> &dimensions) const;
        GeneratorParameters params;
};
