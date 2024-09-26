#include "flatTerrainGenerator.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed, GeneratorType::FLAT)
{}

Heightmap FlatTerrainGenerator::generate(Vector2<int> dimensions){
    Heightmap heightmap;   
    int height = 4; //standard random number
    for(int x=0; x<dimensions.x; x++){
        std::valarray<double> row(dimensions.y);
        for(int y=0; y<dimensions.y; y++){
            row[y] = height;
        }
        heightmap.push_back(row);
    }
    return heightmap;
}