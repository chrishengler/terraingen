#include "flatTerrainGenerator.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed, GeneratorType::FLAT)
{}

Heightmap FlatTerrainGenerator::generate(Vector2<int> dimensions){
    Heightmap heightmap;   
    int height = 4; //standard random number
    for(int x=0; x<dimensions.x; x++){
        std::vector<double> row = std::vector<double>();
        for(int y=0; y<dimensions.y; y++){
            row.push_back(height);
        }
        heightmap.push_back(row);
    }
    return heightmap;
}