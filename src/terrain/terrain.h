#include <vector>

typedef std::vector<std::vector<size_t>> Heightmap;

class Terrain{
    private:
        Heightmap heightmap;
        const size_t size_x, size_y;

    public:
        Terrain(size_t x, size_t y);
        Terrain(Heightmap initialize);
        Heightmap get_terrain();
        size_t get_size_x(){return size_x;}
        size_t get_size_y(){return size_y;}
};
