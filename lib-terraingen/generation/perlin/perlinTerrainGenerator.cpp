#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include "perlinTerrainGenerator.h"
#include "data_types.h"

const double OFFSET = 1;
const double SCALE = 0.5;

std::unique_ptr<PerlinTerrainGenerator> new_perlin_generator() {
    return std::make_unique<PerlinTerrainGenerator>();
}

PerlinTerrainGenerator::PerlinTerrainGenerator()
    : Generator(GeneratorType::PERLIN)
{
}

void PerlinTerrainGenerator::setParameters(const PerlinParameters& params) {
    this->params = params;
}

Heightmap PerlinTerrainGenerator::generate(const Vector2<uint> &dimensions, const uint &seed){
    permutations.clear();
    permutations.reserve(256);
    for(int i=0; i<256; i++)
    {
        permutations.push_back(i);
    }
    std::shuffle(permutations.begin(), permutations.end(), std::mt19937(seed));
    std::cout << "Generating Perlin terrain with dimensions: " << dimensions.x << "x" << dimensions.y << std::endl;
    std::cout << "Using scale: " << params.scale << " and cell size: " << params.cellSize << std::endl;
    Heightmap heightmap;   
    double max=0;
    double min=1;
    for(uint col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(uint row=0; row<dimensions.y; row++){
            auto result = perlin(Vector2<int>(col,row));
            if(result > max)
            {
                max = result;
            }
            if(result < min)
            {
                min = result;
            }
            column[row] = perlin(Vector2<int>(col,row));
        }
        heightmap.push_back(column);
    }
    std::cout << "max: " << max << "\nmin: " << min << std::endl;
    return heightmap;
}

std::unique_ptr<Heightmap> PerlinTerrainGenerator::generate(const uint &x, const uint &y, const uint &seed) {
    auto hm = std::make_unique<Heightmap>(generate(Vector2<uint>{x, y}, seed));
    return hm;
}

double PerlinTerrainGenerator::perlin(const Vector2<int> &coordinates)
{
    double scaled_x = (double)(coordinates.x) * params.scale;
    double scaled_y = (double)(coordinates.y) * params.scale;
    double reduced_x = scaled_x / params.cellSize;
    double reduced_y = scaled_y / params.cellSize;;
    int const floor_x = std::floor(reduced_x);
    int const floor_y = std::floor(reduced_y);

    double x = reduced_x - floor_x;
    double y = reduced_y - floor_y;

    double x_fraction = fade(x);
    double y_fraction = fade(y);

    double const bottom_left = gradient(retrievePermutation(retrievePermutation(floor_x) + floor_y), {x, y});
    double const bottom_right = gradient(retrievePermutation(retrievePermutation((floor_x + 1)) + floor_y), {x-1, y});
    double const top_left = gradient(retrievePermutation(retrievePermutation(floor_x) + floor_y + 1), {x, y-1});
    double const top_right = gradient(retrievePermutation(retrievePermutation((floor_x + 1)) + floor_y + 1), {x-1, y-1});

    double bottom_value = std::lerp(bottom_left, bottom_right, x_fraction);
    double top_value = std::lerp(top_left, top_right, x_fraction);
    auto raw_result = std::lerp(bottom_value, top_value, y_fraction);
    return (raw_result + OFFSET) * SCALE;
}

double PerlinTerrainGenerator::fade(double t)
{
    if(t<0 || t>1){
        std::cout << "t" << t <<std::endl;
    }
    return std::pow(t, 3) * (t * (t * 6 - 15) + 10);
}

double PerlinTerrainGenerator::gradient(int hash, const Vector2<double> &coordinates)
{
    switch (hash & 7)
    {
        case 0: return coordinates.x + coordinates.y;   // (1, 1)
        case 1: return -coordinates.x + coordinates.y;  // (-1, 1)
        case 2: return coordinates.x - coordinates.y;   // (1, -1)
        case 3: return -coordinates.x - coordinates.y;  // (-1, -1)
        case 4: return coordinates.x;                   // (1, 0)
        case 5: return -coordinates.x;                  // (-1, 0)
        case 6: return coordinates.y;                   // (0, 1)
        case 7: return -coordinates.y;                  // (0, -1)
        default: return 0;  // Should not reach here
    }
}

int PerlinTerrainGenerator::retrievePermutation(int permutationIndex)
{
    return permutations[permutationIndex % 256];
}