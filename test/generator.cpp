#include "catch2/catch_test_macros.hpp"

#include "data_types.h"
#include "generatorParameters.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"
#include "diamondsquare/diamondSquareGenerator.h"

TEST_CASE("Generator Tests", "[generator]")
{
    SECTION("Flat terrain generator produces correct output")
    {
        FlatTerrainGenerator ftg;
        Vector2<uint> gridSize(10, 10);
        FlatParameters params{gridSize.x, gridSize.y, 0, 4.0};

        Heightmap result = ftg.generate(params);

        REQUIRE(result.size() == gridSize.x);  // Number of columns
        for (int col = 0; col < gridSize.x; col++)
        {
            REQUIRE(result.at(0).size() == gridSize.y);  // Number of rows
            for (int row = 0; row < gridSize.y; row++)
            {
                REQUIRE(result.at(col)[row] == params.terrainHeight);
            }
        }
    }

    SECTION("Perlin noise generator can be created with seed and parameters")
    {
        Vector2<uint> gridSize(10, 10);
        PerlinParameters pp{gridSize.x, gridSize.y, 4, 2.0, 32};

        PerlinTerrainGenerator ptg1;

        // Verify parameters by generating terrain and checking scale and grid size
        Heightmap result = ptg1.generate(pp);
        REQUIRE(result.size() == gridSize.x);
        REQUIRE(result[0].size() == gridSize.y);
    }
}

TEST_CASE("Perlin generator parameters", "[perlin]")
{
    SECTION("Default scale produces output within range") {
        Vector2<uint> expected_size(512, 512);
        
        PerlinParameters params{ expected_size.x, expected_size.y, 0};

        PerlinTerrainGenerator ptg;
        Heightmap result = ptg.generate(params);

        REQUIRE(result.size() == expected_size.x);  // Number of columns
        for (int col = 0; col < expected_size.x; col++) {
            REQUIRE(result.at(0).size() == expected_size.y);  // Number of rows
            for(int row = 0; row < expected_size.y; row++) {
                auto val = result.at(col)[row];
                REQUIRE(val >= 0);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different scales produce different results") {
        Vector2<uint> expected_size(512, 512);

        PerlinParameters params1{
            expected_size.x, expected_size.y, 4, 1.0, 32,
        };

        PerlinParameters params2{
            expected_size.x, expected_size.y, 4, 2.0, 32,
        };

        PerlinTerrainGenerator pg;
        
        Heightmap result1 = pg.generate(params1);
        Heightmap result2 = pg.generate(params2);

        bool found_different = false;
        for (int col = 0; col < expected_size.x && !found_different; col++) {
            for (int row = 0; row < expected_size.y && !found_different; row++) {
                if (result1[col][row] != result2[col][row]) {
                    found_different = true;
                }
            }
        }
        REQUIRE(found_different);
    }
}

TEST_CASE("Diamond Square generator", "[diamond-square]")
{
    SECTION("Produces correct output within range") {
        Vector2<uint> expected_size(512, 512);
        DiamondSquareParameters params{
            expected_size.x,
            expected_size.y,
            42,
            1.0
        };

        DiamondSquareGenerator dsg;
        Heightmap result = dsg.generate(params);

        REQUIRE(result.size() == expected_size.x);
        for (int x = 0; x < expected_size.x; x++) {
            REQUIRE(result.at(0).size() == expected_size.y);
            for(int y = 0; y < expected_size.y; y++) {
                auto val = result.at(x)[y];
                REQUIRE(val >= 0);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different seeds produce different results") {
        Vector2<uint> expected_size(64, 64);
        DiamondSquareParameters params
        {
            expected_size.x,
            expected_size.y,
            42,
            1.0
        };

        DiamondSquareGenerator dsg;

        Heightmap result1 = dsg.generate(params);

        params.seed = 84;
        Heightmap result2 = dsg.generate(params);

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
}