#include <algorithm>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include "terrainCombination.h"

Heightmap TerrainCombination::combineTerrains(const std::vector<Heightmap> terrains, const std::vector<float> weights)
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

    float sumWeights = std::accumulate(weights.begin(), weights.end(), 0.0f);
    if(sumWeights <= 0)
    {
        throw std::invalid_argument((std::stringstream() << "Sum of weights is " << sumWeights << " but must be > 0").str());
    }
    std::vector<float> normalised_weights;
    normalised_weights.reserve(weights.size());

    for (float w : weights) {
        normalised_weights.push_back(w / sumWeights);
    }

    std::vector<Heightmap> scaledHeightmaps(numTerrains);
    for(unsigned int i=0; i<numTerrains; i++)
    {
        Heightmap scaledHeightmap(terrains[i]);
        for(int j=0; j<dimensions.x; j++)
        {
            scaledHeightmap[j] *= normalised_weights[i];
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
        
struct HeightmapHandle{
    Heightmap* addr;
};

std::unique_ptr<Heightmap> combine(const std::vector<HeightmapHandle>& heightmap_handles, const std::vector<float>& weights){
    std::vector<Heightmap> heightmaps;
    heightmaps.reserve(heightmap_handles.size());
    for(auto handle: heightmap_handles){
        heightmaps.push_back(*(handle.addr));
    }
    return std::make_unique<Heightmap>(TerrainCombination::combineTerrains(heightmaps, weights));
}