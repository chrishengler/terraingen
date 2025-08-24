#pragma once
#include "generator.h"
#include "data_types.h"
#include "generatorParameters.h"

class DiamondSquareGenerator : public Generator{
    public:
        DiamondSquareGenerator(unsigned int seed);
        Heightmap generate(const Vector2<uint> &dimensions) override;
        void setParameters(const DiamondSquareParameters& params);

        std::unique_ptr<Heightmap> generate_as_unique_ptr(const uint &x, const uint &y) override;
    private:
        int get_required_grid_size(const Vector2<uint> &dimensions) const;
        DiamondSquareParameters params;
};
