#pragma once
#include "data_types.h"

class Terrain{
    private:
        Heightmap heightmap;
        const unsigned int size_x, size_y;

    public:
        Terrain(unsigned int x, unsigned int y);
        Terrain(Heightmap initialize);
        Heightmap getTerrain(){return heightmap;}
        size_t getSizeX(){return size_x;}
        size_t getSizeY(){return size_y;}
        Vector2<unsigned int> getDimensions(){return {size_x, size_y};}
};
