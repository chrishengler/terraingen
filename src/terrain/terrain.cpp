#include "terrain.h"

#include <iostream>

Terrain::Terrain(unsigned int x, unsigned int y)
    : size_x(x), size_y(y)
{
    heightmap = std::vector<std::vector<double>>(size_x);
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = std::vector<double>(size_y);
    }
}

Terrain::Terrain(Heightmap _heightmap):
size_x(_heightmap.capacity()), size_y(_heightmap.at(0).capacity())
{
    heightmap = std::vector<std::vector<double>>(size_x);
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = _heightmap.at(i);
    }
}

Heightmap Terrain::get_terrain(){
    return heightmap;
}