#pragma once
#include "data_types.h"

class Terrain{
    private:
        Heightmap heightmap;
        const uint size_x, size_y;

    public:
        Terrain(uint x, uint y);
        Terrain(Heightmap initialize);
        Heightmap getTerrain(){return heightmap;}
        size_t getSizeX(){return size_x;}
        size_t getSizeY(){return size_y;}
        Vector2<uint> getDimensions(){return {size_x, size_y};}
};
