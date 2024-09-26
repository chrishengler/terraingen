#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "terrainCombination.h"
#include <iostream>

TEST_CASE("Terrain combination")
{
    TerrainCombination terrainCombination;
    Heightmap heightmap1 = {{0., 0.5, 1.}, {1., 1., 1.}};
    Heightmap heightmap2 = {{0., 0., 0.}, {1., 1., 1.}};
    Heightmap heightmap3 = {{0., 0.25, 0.5}, {0., 0., 0.}};

    SECTION("adding terrains of different sizes fails")
    {
        Heightmap wrongSize = {{0.1, 0.2, 0.3, 0.4}, {0.2,0.3,0.4}};
        CHECK_THROWS(terrainCombination.combineTerrains({heightmap1, wrongSize}, {0.5,0.5}));
    }

    SECTION("wrong number of weights fails")
    {
        CHECK_THROWS(terrainCombination.combineTerrains({heightmap1, heightmap2}, {0.5, 0.3, 0.2}));
    }

    SECTION("wrong total weights fails")
    {
        CHECK_THROWS(terrainCombination.combineTerrains({heightmap1, heightmap2}, {0.1, 0.1}));
    }

    SECTION("adding two terrains with equal weight")
    {
        Heightmap average = {{0., 0.25, 0.5}, {1., 1., 1.}};

        std::vector<Terrain> terrainsToCombine = {heightmap1, heightmap2};
        std::vector<float> weights = {0.5, 0.5};
        auto result = terrainCombination.combineTerrains(terrainsToCombine, weights);
        auto terrain = result.getTerrain();
        for (int i = 0; i < terrain.size(); i++)
        {
            for (int j = 0; j < terrain[i].size(); j++)
            {
                REQUIRE_THAT(terrain[i][j], Catch::Matchers::WithinRel(average[i][j], 0.0001));
            }
        }
    }

    SECTION("adding three terrains with equal weights")
    {
        Heightmap average = {{0., 0.25, 0.5}, {2./3, 2./3, 2./3}};

        std::vector<Terrain> terrainsToCombine = {heightmap1, heightmap2, heightmap3};
        std::vector<float> weights = {1./3, 1./3, 1./3};
        auto result = terrainCombination.combineTerrains(terrainsToCombine, weights);
        auto terrain = result.getTerrain();
        for (int i = 0; i < terrain.size(); i++)
        {
            for (int j = 0; j < terrain[i].size(); j++)
            {
                REQUIRE_THAT(terrain[i][j], Catch::Matchers::WithinRel(average[i][j], 0.0001));
            }
        }

    }
}