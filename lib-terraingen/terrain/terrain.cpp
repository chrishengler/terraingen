#include "terrain.h"

Terrain::Terrain(int x, int y)
    : size_x(x), size_y(y)
{
    if(size_x <= 0 || size_y <= 0)
    {
        // TODO: specific exception
        throw std::exception();
    }
    heightmap = std::vector<std::valarray<double>>(size_x);
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = std::valarray<double>(size_y);
    }
}

Terrain::Terrain(Heightmap _heightmap):
size_x(_heightmap.size()), size_y(_heightmap.at(0).size())
{
    heightmap = std::vector<std::valarray<double>>(size_x);
    for(int x=1; x<_heightmap.size(); x++)
    {
        if(_heightmap.at(x).size() != size_y)
        {
            // TODO: specific exception
            throw std::exception();
        }
    }
    for(int i=0; i<size_x; i++)
    {
        heightmap[i] = _heightmap.at(i);
    }
}