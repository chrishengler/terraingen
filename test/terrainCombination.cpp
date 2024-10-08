#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "terrainCombination.h"

TEST_CASE("Terrain combination")
{
    TerrainCombination terrainCombination;
    Heightmap heightmap1 = {{0., 0.5, 1.}, {1., 1., 1.}};
    Heightmap heightmap2 = {{0., 0., 0.}, {1., 1., 1.}};
    Heightmap heightmap3 = {{0., 0.25, 0.5}, {0., 0., 0.}};

    SECTION("adding terrains of different sizes fails")
    {
        Heightmap wrongSize = {{0.1, 0.2, 0.3, 0.4}, {0.2, 0.3, 0.4, 0.3}};
        REQUIRE_THROWS_AS(terrainCombination.combineTerrains({heightmap1, wrongSize}, {0.5,0.5}), std::invalid_argument);
    }

    SECTION("wrong number of weights fails")
    {
        REQUIRE_THROWS_AS(terrainCombination.combineTerrains({heightmap1, heightmap2}, {0.5, 0.3, 0.2}), std::invalid_argument);
    }

    SECTION("wrong total weights fails")
    {
        REQUIRE_THROWS_AS(terrainCombination.combineTerrains({heightmap1, heightmap2}, {0.1, 0.1}), std::invalid_argument);
    }

    SECTION("adding two terrains with equal weight")
    {
        std::vector<Terrain> terrainsToCombine = {heightmap1, heightmap2};
        std::vector<float> weights = {0.5, 0.5};

        Heightmap expectedResult = {{0., 0.25, 0.5}, {1., 1., 1.}};

        auto result = terrainCombination.combineTerrains(terrainsToCombine, weights);
        auto terrain = result.getTerrain();
        for (int i = 0; i < terrain.size(); i++)
        {
            for (int j = 0; j < terrain[i].size(); j++)
            {
                REQUIRE_THAT(terrain[i][j], Catch::Matchers::WithinRel(expectedResult[i][j], 0.0001));
            }
        }
    }

    SECTION("adding three terrains with equal weights")
    {
        std::vector<Terrain> terrainsToCombine = {heightmap1, heightmap2, heightmap3};
        std::vector<float> weights = {1./3, 1./3, 1./3};

        Heightmap expectedResult = {{0., 0.25, 0.5}, {2./3, 2./3, 2./3}};

        auto result = terrainCombination.combineTerrains(terrainsToCombine, weights);
        auto terrain = result.getTerrain();
        for (int i = 0; i < terrain.size(); i++)
        {
            for (int j = 0; j < terrain[i].size(); j++)
            {
                REQUIRE_THAT(terrain[i][j], Catch::Matchers::WithinRel(expectedResult[i][j], 0.0001));
            }
        }

    }

    SECTION("adding multiple terrains with unequal weights")
    {
        std::vector<Terrain> terrainsToCombine = {heightmap1, heightmap2, heightmap3};
        std::vector<float> weights = {0.5, 0.2, 0.3};

        Heightmap expectedResult = {{0, 0.325, 0.65}, {0.7, 0.7, 0.7}};
        auto result = terrainCombination.combineTerrains(terrainsToCombine, weights);
        auto terrain = result.getTerrain();
        for (int i = 0; i < terrain.size(); i++)
        {
            for (int j = 0; j < terrain[i].size(); j++)
            {
                REQUIRE_THAT(terrain[i][j], Catch::Matchers::WithinRel(expectedResult[i][j], 0.0001));
            }
        }

    }
}