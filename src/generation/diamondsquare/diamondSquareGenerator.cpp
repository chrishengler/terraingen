#include "diamondSquareGenerator.h"
#include "data_types.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <limits>

DiamondSquareGenerator::DiamondSquareGenerator(unsigned int seed, const Vector2<int> &cell_sizes)
    : Generator(seed, GeneratorType::DIAMOND_SQUARE), cell_sizes(cell_sizes)
{
}

Heightmap DiamondSquareGenerator::generate(Vector2<int> dimensions)
{
    int grid_size = std::pow(2, get_required_grid_size(dimensions)) + 1;
    
    Heightmap heightmap;
    heightmap.reserve(grid_size);
    for(int x = 0; x < grid_size; x++) {
        std::valarray<double> row(0.0, grid_size);
        heightmap.push_back(row);
    }

    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    
    heightmap[0][0] = dist(rng);
    heightmap[0][grid_size-1] = dist(rng);
    heightmap[grid_size-1][0] = dist(rng);
    heightmap[grid_size-1][grid_size-1] = dist(rng);

    double roughness = 1.0;
    for(int step = grid_size - 1; step > 1; step /= 2) {
        int half_step = step / 2;

        for(int x = half_step; x < grid_size - half_step; x += step) {
            for(int y = half_step; y < grid_size - half_step; y += step) {
                double avg = (heightmap[x-half_step][y-half_step] +
                            heightmap[x-half_step][y+half_step] +
                            heightmap[x+half_step][y-half_step] +
                            heightmap[x+half_step][y+half_step]) / 4.0;
                heightmap[x][y] = avg + dist(rng) * roughness;
            }
        }

        for(int x = 0; x < grid_size; x += half_step) {
            for(int y = (x + half_step) % step; y < grid_size; y += step) {
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
    
    double min_val;
    double max_val;
    
    // Normalize to range [-1, 1] as the random variations can push high/low values
    // outside expected range
    for(int x = 0; x < dimensions.x; x++) {
        for(int y = 0; y < dimensions.y; y++) {
            min_val = std::min(min_val, heightmap[x][y]);
            max_val = std::max(max_val, heightmap[x][y]);
        }
    }
    
    double range = max_val - min_val;
    
    for(int x = 0; x < dimensions.x; x++) {
        std::valarray<double> row(dimensions.y);
        for(int y = 0; y < dimensions.y; y++) {
            row[y] = 2.0 * ((heightmap[x][y] - min_val) / range) - 1.0;
        }
        final_heightmap.push_back(row);
    }

    return final_heightmap;
}

int DiamondSquareGenerator::get_required_grid_size(const Vector2<int> &dimensions) const
{
    return std::ceil(std::log2(std::max(dimensions.x, dimensions.y)));
}
