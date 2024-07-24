#include <vector>

typedef std::vector<std::vector<unsigned int>> Heightmap;

class Generator{
    public:
        Generator(unsigned int seed);
        virtual Heightmap generate(unsigned int size_x, unsigned int size_y) = 0;

    private:
        unsigned int seed;
};