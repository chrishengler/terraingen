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
    Vector2<int> expected_size(512,512);

    SECTION("Default scale") {
        PerlinTerrainGenerator ptg(0, cell_sizes);
        Heightmap result = ptg.generate(expected_size);

        REQUIRE(result.size() == expected_size.x);
        for (int x=0; x<expected_size.x; x++) {
            REQUIRE(result.at(0).size() == expected_size.y);
            for(int y = 0; y<expected_size.y; y++) {
                auto val = result.at(x)[y];
                REQUIRE(val >= -1);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different scales produce different results") {
        PerlinTerrainGenerator ptg1(42, cell_sizes, 1.0);
        PerlinTerrainGenerator ptg2(42, cell_sizes, 2.0);
        
        Heightmap result1 = ptg1.generate(expected_size);
        Heightmap result2 = ptg2.generate(expected_size);

        bool found_different = false;
        for (int x = 0; x < expected_size.x && !found_different; x++) {
            for (int y = 0; y < expected_size.y && !found_different; y++) {
                if (result1[x][y] != result2[x][y]) {
                    found_different = true;
                }
            }
        }
        REQUIRE(found_different);
    }

    SECTION("Scale can be changed after construction") {
        PerlinTerrainGenerator ptg(42, cell_sizes, 1.0);
        Heightmap result1 = ptg.generate(expected_size);
        
        ptg.setScale(2.0);
        Heightmap result2 = ptg.generate(expected_size);

        bool found_different = false;
        for (int x = 0; x < expected_size.x && !found_different; x++) {
            for (int y = 0; y < expected_size.y && !found_different; y++) {
                if (result1[x][y] != result2[x][y]) {
                    found_different = true;
                }
            }
        }
        REQUIRE(found_different);
        REQUIRE(ptg.getScale() == 2.0);
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