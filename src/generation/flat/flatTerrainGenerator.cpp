#include "flatTerrainGenerator.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed)
{}

Heightmap FlatTerrainGenerator::generate(unsigned int size_x, unsigned int size_y){
    Heightmap heightmap;   
    unsigned int height = 4; //standard random number
    for(int x=0; x<size_x; x++){
        std::vector<unsigned int> row = std::vector<unsigned int>();
        for(int y=0; y<size_y; y++){
            row.push_back(height);
        }
        heightmap.push_back(row);
    }
    return heightmap;
}