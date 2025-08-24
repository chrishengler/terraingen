#pragma once
#include "generator.h"
#include "data_types.h"
#include "generatorParameters.h"

class DiamondSquareGenerator : public Generator{
    public:
        DiamondSquareGenerator(unsigned int seed);
        Heightmap generate(const Vec2i &dimensions) override;
        void setParameters(const DiamondSquareParameters& params);

        std::unique_ptr<Heightmap> generate_as_unique_ptr(const Vec2i &dimensions) override;
    private:
        int get_required_grid_size(const Vector2<int> &dimensions) const;
        DiamondSquareParameters params;
};
