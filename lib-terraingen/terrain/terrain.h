#pragma once
#include <cstdint>
#include "data_types.h"

class Terrain{
    private:
        Heightmap heightmap;
        const uint32_t size_x, size_y;

    public:
        Terrain(uint32_t x, uint32_t y);
        Terrain(Heightmap initialize);
        Heightmap getTerrain(){return heightmap;}
        size_t getSizeX(){return size_x;}
        size_t getSizeY(){return size_y;}
        Vector2<uint32_t> getDimensions(){return {size_x, size_y};}
};
