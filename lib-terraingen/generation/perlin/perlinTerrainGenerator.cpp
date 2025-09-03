#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include "perlinTerrainGenerator.h"
#include "data_types.h"
#include "generatorParameters.h"

const double OFFSET = 1;
const double SCALE = 0.5;

std::unique_ptr<PerlinTerrainGenerator> new_perlin_generator() {
    return std::make_unique<PerlinTerrainGenerator>();
}

Heightmap PerlinTerrainGenerator::generate(const PerlinParameters &params) const{
    std::vector<int> permutations;
    Vector2<uint32_t> dimensions{params.cols, params.rows};
    permutations.reserve(256);
    for(int i=0; i<256; i++)
    {
        permutations.push_back(i);
    }
    std::shuffle(permutations.begin(), permutations.end(), std::mt19937(params.seed));
    Heightmap heightmap;   
    double max=0;
    double min=1;
    for(uint32_t col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(uint32_t row=0; row<dimensions.y; row++){
            auto result = perlin(Vector2<int>(col,row), permutations, params);
            if(result > max)
            {
                max = result;
            }
            if(result < min)
            {
                min = result;
            }
            column[row] = perlin(Vector2<int>(col,row), permutations, params);
        }
        heightmap.push_back(column);
    }
    return heightmap;
}

std::unique_ptr<std::vector<float>> PerlinTerrainGenerator::generate_flat(const PerlinParameters &params) const {
    std::cout << "generating perlin with cols: " << params.cols << " and rows: " << params.rows;
    std::cout << "length when flattened = " << params.cols * params.rows * 3 << std::endl;
    auto hm = generate(params);
    return std::make_unique<std::vector<float>>(flattenHeightmap(hm));
}

double PerlinTerrainGenerator::perlin(const Vector2<int> &coordinates, const std::vector<int> &permutations, const PerlinParameters &params) const
{
    double scaled_x = (double)(coordinates.x) * params.scale;
    double scaled_y = (double)(coordinates.y) * params.scale;
    double reduced_x = scaled_x / params.cellSize;
    double reduced_y = scaled_y / params.cellSize;;
    int const floor_x = (int const)std::floor(reduced_x);
    int const floor_y = (int const)std::floor(reduced_y);

    double x = reduced_x - floor_x;
    double y = reduced_y - floor_y;

    double x_fraction = fade(x);
    double y_fraction = fade(y);

    auto retrievePermutation = [&permutations](const int &index) -> int {return permutations[index % 256];};
    double const bottom_left = gradient(retrievePermutation(retrievePermutation(floor_x) + floor_y), {x, y});
    double const bottom_right = gradient(retrievePermutation(retrievePermutation((floor_x + 1)) + floor_y), {x-1, y});
    double const top_left = gradient(retrievePermutation(retrievePermutation(floor_x) + floor_y + 1), {x, y-1});
    double const top_right = gradient(retrievePermutation(retrievePermutation((floor_x + 1)) + floor_y + 1), {x-1, y-1});

    double bottom_value = std::lerp(bottom_left, bottom_right, x_fraction);
    double top_value = std::lerp(top_left, top_right, x_fraction);
    auto raw_result = std::lerp(bottom_value, top_value, y_fraction);
    return (raw_result + OFFSET) * SCALE;
}

double PerlinTerrainGenerator::fade(double t) const
{
    return std::pow(t, 3) * (t * (t * 6 - 15) + 10);
}

double PerlinTerrainGenerator::gradient(int hash, const Vector2<double> &coordinates) const
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