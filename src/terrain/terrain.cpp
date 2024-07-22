#include "terrain.h"

#include <iostream>

Terrain::Terrain(size_t x, size_t y)
    : size_x(x), size_y(y)
{
    heightmap = std::vector<std::vector<size_t>>(size_x);
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = std::vector<size_t>(size_y);
    }

    std::cout << heightmap.capacity() << std::endl;
}

Terrain::Terrain(Heightmap _heightmap):
size_x(_heightmap.capacity()), size_y(_heightmap.at(0).capacity())
{
    heightmap = std::vector<std::vector<size_t>>(size_x);
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = _heightmap.at(i);
    }
}

Heightmap Terrain::get_terrain(){
    return heightmap;
}