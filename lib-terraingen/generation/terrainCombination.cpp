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
    if(sumWeights != 1)
    {
        throw std::invalid_argument((std::stringstream() << "Sum of weights is " << sumWeights << " but must be 1").str());
    }

    std::vector<Heightmap> scaledHeightmaps(numTerrains);
    for(unsigned int i=0; i<numTerrains; i++)
    {
        Heightmap scaledHeightmap(terrains[i]);
        for(unsigned int j=0; j<dimensions.x; j++)
        {
            scaledHeightmap[j] *= weights[i];
        }
        scaledHeightmaps[i] = (scaledHeightmap);
    }

    Heightmap combinedHeightmap(dimensions.x);
    for (unsigned int i = 0; i < dimensions.x; i++)
    {
        auto row = std::valarray<double>(dimensions.y);
        std::for_each(scaledHeightmaps.begin(), scaledHeightmaps.end(), [&row, i](auto &hm){row += hm.at(i);});
        combinedHeightmap[i] = row;
    }

    return combinedHeightmap;
}