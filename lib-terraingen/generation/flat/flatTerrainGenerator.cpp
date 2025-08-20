#include "flatTerrainGenerator.h"

FlatTerrainGenerator::FlatTerrainGenerator(unsigned int seed)
    : Generator(seed, GeneratorType::FLAT)
{}

Heightmap FlatTerrainGenerator::generate(Vector2<int> dimensions){
    Heightmap heightmap;   
    int height = 4; //standard random number
    for(int col=0; col<dimensions.x; col++){
        std::valarray<double> column(dimensions.y);
        for(int row=0; row<dimensions.y; row++){
            column[row] = height;
        }
        heightmap.push_back(column);
    }
    return heightmap;
}