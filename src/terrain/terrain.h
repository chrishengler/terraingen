#include <vector>

typedef std::vector<std::vector<unsigned int>> Heightmap;

class Terrain{
    private:
        Heightmap heightmap;
        const unsigned int size_x, size_y;

    public:
        Terrain(unsigned int x, unsigned int y);
        Terrain(Heightmap initialize);
        Heightmap get_terrain();
        size_t get_size_x(){return size_x;}
        size_t get_size_y(){return size_y;}
};
