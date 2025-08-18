#include "catch2/catch_test_macros.hpp"

#include "diamondsquare/diamondSquareGenerator.h"
#include "terrain/terrain.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"

TEST_CASE("Flat terrain generator")
{
    FlatTerrainGenerator ftg(0);
    Heightmap result = ftg.generate(Vector2<int>(2, 3));

    REQUIRE(result.size() == 2);
    for (int x = 0; x < 2; x++)
    {
        REQUIRE(result.at(0).size() == 3);
        for (int y = 0; y < 3; y++)
        {
            REQUIRE(result.at(x)[y] == 4);
        }
    }
}

TEST_CASE("Perlin generator")
{
    Vector2<int> cell_sizes(16,16);
    PerlinTerrainGenerator ptg(0, cell_sizes);
    Vector2<int> expected_size(512,512);
    Heightmap result = ptg.generate(expected_size);

    double max_abs_value = std::sqrt(2);
    REQUIRE(result.size() == expected_size.x);
    for (int x=0; x<expected_size.x; x++)
    {
        REQUIRE(result.at(0).size() == expected_size.y);
        for(int y = 0; y<expected_size.y; y++)
        {
            auto val = result.at(x)[y];
            REQUIRE(val >= -1);
            REQUIRE(val <= 1);
        }
    }
}

TEST_CASE("Diamond Square generator")
{
    Vector2<int> cell_sizes(16,16);
    DiamondSquareGenerator dsg(42, cell_sizes);
    Vector2<int> expected_size(512,512);
    Heightmap result = dsg.generate(expected_size);

    REQUIRE(result.size() == expected_size.x);
    for (int x=0; x<expected_size.x; x++)
    {
        REQUIRE(result.at(0).size() == expected_size.y);
        for(int y = 0; y<expected_size.y; y++)
        {
            auto val = result.at(x)[y];
            REQUIRE(val >= -1);
            REQUIRE(val <= 1);
        }
    }
}