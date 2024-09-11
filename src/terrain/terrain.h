#include "data_types.h"

class Terrain{
    private:
        Heightmap heightmap;
        const unsigned int size_x, size_y;

    public:
        Terrain(unsigned int x, unsigned int y);
        Terrain(Heightmap initialize);
        Heightmap get_terrain(){return heightmap;}
        size_t get_size_x(){return size_x;}
        size_t get_size_y(){return size_y;}
};
