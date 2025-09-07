#include <algorithm>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include "terrainCombination.h"

Heightmap TerrainCombination::combineTerrains(std::vector<Heightmap> terrains, std::vector<float> weights)
{
    auto numTerrains = terrains.size();
    if(numTerrains < 2)
    {
        throw std::invalid_argument("Combining terrains requires at least two terrains");
    }
    auto dimensions = getDimensions(terrains[0]);

    if(weights.size() != numTerrains)
    {
        throw std::invalid_argument("Combining terrains requires list of terrains and list of weights of the same length");
    }
    for(unsigned int i=1; i<numTerrains; i++){
        if(getDimensions(terrains[i]) != dimensions){
            throw std::invalid_argument("Combining terrians requires terrains with the same dimensions");
        }
    }

    auto sumWeights = std::accumulate(weights.begin(), weights.end(), (float)0);
    if(sumWeights <= 0)
    {
        throw std::invalid_argument((std::stringstream() << "Sum of weights is " << sumWeights << " but must be > 0").str());
    }
    std::for_each(weights.begin(), weights.end(), [&sumWeights](float &element){element /= sumWeights;});

    std::vector<Heightmap> scaledHeightmaps(numTerrains);
    for(unsigned int i=0; i<numTerrains; i++)
    {
        Heightmap scaledHeightmap(terrains[i]);
        for(int j=0; j<dimensions.x; j++)
        {
            scaledHeightmap[j] *= weights[i];
        }
        scaledHeightmaps[i] = (scaledHeightmap);
    }

    Heightmap combinedHeightmap(dimensions.x);
    for (int i = 0; i < dimensions.x; i++)
    {
        auto row = std::valarray<double>(dimensions.y);
        std::for_each(scaledHeightmaps.begin(), scaledHeightmaps.end(), [&row, i](auto &hm){row += hm.at(i);});
        combinedHeightmap[i] = row;
    }

    return combinedHeightmap;
}
        

std::unique_ptr<Heightmap> combine(std::unique_ptr<std::vector<Heightmap>> heightmaps, std::unique_ptr<std::vector<float>> weights){
    return std::make_unique<Heightmap>(TerrainCombination::combineTerrains(*heightmaps, *weights));
}