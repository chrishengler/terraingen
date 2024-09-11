#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "perlinTerrainGenerator.h"

PerlinTerrainGenerator::PerlinTerrainGenerator(unsigned int seed, const Vector2<unsigned int> &cell_sizes)
    : Generator(seed, GeneratorType::PERLIN), cell_sizes(cell_sizes)
{
    permutations.reserve(256);
    for(int i=0; i<256; i++)
    {
        permutations.push_back(i);
    }
    std::shuffle(permutations.begin(), permutations.end(), std::mt19937(seed));
}

Heightmap PerlinTerrainGenerator::generate(Vector2<unsigned int> dimensions){
    Heightmap heightmap;   
    for(int x=0; x<dimensions.x; x++){
        std::vector<double> row;
        for(int y=0; y<dimensions.y; y++){
            row.push_back(128 * perlin(Vector2<int>(x,y)) + 128);
        }
        heightmap.push_back(row);
    }
    return heightmap;
}

double PerlinTerrainGenerator::perlin(const Vector2<int> &coordinates)
{
    double reduced_x = (double)(coordinates.x % 256)/ cell_sizes.x;
    double reduced_y = (double)(coordinates.y % 256)/ cell_sizes.y;
    int const floor_x = std::floor(reduced_x);
    int const floor_y = std::floor(reduced_y);

    double x = reduced_x - floor_x;
    double y = reduced_y - floor_y;

    double x_fraction = fade(x);
    double y_fraction = fade(y);

    double const bottom_left = gradient(permutations[permutations[floor_x] + floor_y], {x, y});
    double const bottom_right = gradient(permutations[permutations[floor_x + 1] + floor_y], {x-1, y});
    double const top_left = gradient(permutations[permutations[floor_x] + floor_y + 1], {x, y-1});
    double const top_right = gradient(permutations[permutations[floor_x + 1] + floor_y + 1], {x-1, y-1});

    double bottom_value = std::lerp(bottom_left, bottom_right, x_fraction);
    double top_value = std::lerp(top_left, top_right, x_fraction);
    return std::lerp(bottom_value, top_value, y_fraction);
}

double PerlinTerrainGenerator::fade(double t)
{
    return std::pow(t, 3) * (t * (t * 6 - 15) + 10);
}

double PerlinTerrainGenerator::gradient(int hash, const Vector2<double> &coordinates)
{
      int h = hash&7;                      
      
      double u = h<4 ? coordinates.x : coordinates.y;
      double v = h < 4 ? coordinates.y : h == 12 || h == 14 ? coordinates.x
                                                            : 0;
      return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}