#include "diamondSquareGenerator.h"
#include "data_types.h"
#include "generatorParameters.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>
#include <sys/types.h>

std::unique_ptr<DiamondSquareGenerator> new_diamond_square_generator() {
    return std::make_unique<DiamondSquareGenerator>();
}

DiamondSquareGenerator::DiamondSquareGenerator()
    : Generator(GeneratorType::DIAMOND_SQUARE)
{
}

void DiamondSquareGenerator::setParameters(const DiamondSquareParameters& params)
{
    this->params = params;
}

Heightmap DiamondSquareGenerator::generate(const Vector2<uint> &dimensions, const uint &seed) const
{
    std::cout << "Generating Diamond-Square terrain with dimensions: " << dimensions.x << "x" << dimensions.y << std::endl;
    std::cout << "Using roughness: " << params.roughness << std::endl;
    uint grid_size = std::pow(2, get_required_grid_size(dimensions)) + 1;
    
    Heightmap heightmap;
    heightmap.reserve(grid_size);
    for(uint col = 0; col < grid_size; col++) {
        std::valarray<double> column(0.0, grid_size);
        heightmap.push_back(column);
    }

    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    
    heightmap[0][0] = dist(rng);
    heightmap[0][grid_size-1] = dist(rng);
    heightmap[grid_size-1][0] = dist(rng);
    heightmap[grid_size-1][grid_size-1] = dist(rng);

    double roughness = 1.0;
    for(uint step = grid_size - 1; step > 1; step /= 2) {
        uint half_step = step / 2;

        for(uint x = half_step; x < grid_size - half_step; x += step) {
            for(uint y = half_step; y < grid_size - half_step; y += step) {
                double avg = (heightmap[x-half_step][y-half_step] +
                            heightmap[x-half_step][y+half_step] +
                            heightmap[x+half_step][y-half_step] +
                            heightmap[x+half_step][y+half_step]) / 4.0;
                heightmap[x][y] = avg + dist(rng) * roughness;
            }
        }

        for(uint x = 0; x < grid_size; x += half_step) {
            for(uint y = (x + half_step) % step; y < grid_size; y += step) {
                double sum = 0.0;
                int count = 0;

                if(x >= half_step) { 
                    sum += heightmap[x-half_step][y];
                    count++;
                }
                if(x + half_step < grid_size) {
                    sum += heightmap[x+half_step][y];
                    count++;
                }
                if(y >= half_step) {
                    sum += heightmap[x][y-half_step];
                    count++;
                }
                if(y + half_step < grid_size) {
                    sum += heightmap[x][y+half_step];
                    count++;
                }

                heightmap[x][y] = (sum / count) + dist(rng) * roughness;
            }
        }

        roughness *= 0.5;
    }

    Heightmap final_heightmap;
    final_heightmap.reserve(dimensions.x);
    
    double min_val = std::numeric_limits<double>::max();
    double max_val = std::numeric_limits<double>::lowest();
    
    // Normalize to range [-1, 1] as the random variations can push high/low values
    // outside expected range
    for(uint col = 0; col < dimensions.x; col++) {
        for(uint row = 0; row < dimensions.y; row++) {
            min_val = std::min(min_val, heightmap[col][row]);
            max_val = std::max(max_val, heightmap[col][row]);
        }
    }
    
    double range = max_val - min_val;
    
    for(uint col = 0; col < dimensions.x; col++) {
        std::valarray<double> column(dimensions.y);
        for(uint row = 0; row < dimensions.y; row++) {
            column[row] = (heightmap[col][row] - min_val) / range;
        }
        final_heightmap.push_back(column);
    }

    return final_heightmap;
}

std::unique_ptr<std::vector<float>> DiamondSquareGenerator::generate_flat(const uint &x, const uint &y, const uint &seed) const {
    auto hm = generate(Vector2<uint>{x, y}, seed);
    return std::make_unique<std::vector<float>>(flattenHeightmap(hm));
}

int DiamondSquareGenerator::get_required_grid_size(const Vector2<uint> &dimensions) const
{
    return std::ceil(std::log2(std::max(dimensions.x, dimensions.y)));
}
