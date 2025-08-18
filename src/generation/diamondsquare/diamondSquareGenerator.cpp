#include "diamondSquareGenerator.h"
#include "data_types.h"

DiamondSquareGenerator::DiamondSquareGenerator(unsigned int seed, const Vector2<int> &cell_sizes)
    : Generator(seed, GeneratorType::DIAMOND_SQUARE), cell_sizes(cell_sizes)
{
    
}

Heightmap DiamondSquareGenerator::generate(Vector2<int> dimensions)
{
    Heightmap heightmap;
    return heightmap;
}

double DiamondSquareGenerator::get_required_grid_size(const Vector2<int> &dimensions) const
{
    return std::max(dimensions.x, dimensions.y);
}

double DiamondSquareGenerator::fade(double t)
{
    return 4;
}

double DiamondSquareGenerator::gradient(const int hash, const Vector2<double> &coordinates)
{
    return 4;
}

int DiamondSquareGenerator::retrievePermutation(int permutationIndex)
{
    return 4;
}