#pragma once
#include "generator.h"
#include "data_types.h"
#include "generatorParameters.h"

class DiamondSquareGenerator : public Generator{
    public:
        DiamondSquareGenerator();
        Heightmap generate(const Vector2<uint> &dimensions, const uint &seed) override;
        void setParameters(const DiamondSquareParameters& params);

        std::unique_ptr<Heightmap> generate(const uint &x, const uint &y, const uint &seed) override;
    private:
        int get_required_grid_size(const Vector2<uint> &dimensions) const;
        DiamondSquareParameters params;
};
