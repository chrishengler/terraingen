#include "catch2/catch_test_macros.hpp"

#include "generatorParameters.h"
#include "terrain/terrain.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"
#include "diamondsquare/diamondSquareGenerator.h"

TEST_CASE("Generator Tests", "[generator]")
{
    SECTION("Flat terrain generator produces correct output")
    {
        FlatTerrainGenerator ftg(0);
        FlatParameters params;
        params.gridSize = {2, 3};
        params.height = 4.0;
        ftg.setParameters(params);

        Heightmap result = ftg.generate(params.gridSize);

        REQUIRE(result.size() == params.gridSize.x);  // Number of columns
        for (int col = 0; col < params.gridSize.x; col++)
        {
            REQUIRE(result.at(0).size() == params.gridSize.y);  // Number of rows
            for (int row = 0; row < params.gridSize.y; row++)
            {
                REQUIRE(result.at(col)[row] == params.height);
            }
        }
    }

    SECTION("Perlin noise generator can be created with seed and parameters")
    {
        PerlinParameters pp2;
        pp2.scale = 2.0f;
        pp2.cellSize = 32;
        pp2.gridSize = {10, 10};

        PerlinTerrainGenerator ptg1(4);
        ptg1.setParameters(pp2);

        // Verify parameters by generating terrain and checking scale and grid size
        Heightmap result = ptg1.generate(pp2.gridSize);
        REQUIRE(result.size() == pp2.gridSize.x);
        REQUIRE(result[0].size() == pp2.gridSize.y);

        // Create a second generator to verify independent parameter handling
        PerlinTerrainGenerator ptg2(8);
        ptg2.setParameters(pp2);
        result = ptg2.generate(pp2.gridSize);
        REQUIRE(result.size() == pp2.gridSize.x);
        REQUIRE(result[0].size() == pp2.gridSize.y);
    }
}

TEST_CASE("Perlin generator parameters", "[perlin]")
{
    SECTION("Default scale produces output within range") {
        Vector2<int> expected_size(512, 512);
        
        PerlinParameters params;
        params.gridSize = expected_size;

        PerlinTerrainGenerator ptg(0);
        ptg.setParameters(params);
        Heightmap result = ptg.generate(params.gridSize);

        REQUIRE(result.size() == expected_size.x);  // Number of columns
        for (int col = 0; col < expected_size.x; col++) {
            REQUIRE(result.at(0).size() == expected_size.y);  // Number of rows
            for(int row = 0; row < expected_size.y; row++) {
                auto val = result.at(col)[row];
                REQUIRE(val >= -1);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different scales produce different results") {
        Vector2<int> expected_size(512, 512);

        PerlinParameters params1;
        params1.scale = 1.0f;
        params1.cellSize = 32;
        params1.gridSize = expected_size;

        PerlinParameters params2;
        params2.scale = 2.0f;
        params2.cellSize = 32;
        params2.gridSize = expected_size;

        PerlinTerrainGenerator ptg1(4);
        ptg1.setParameters(params1);
        PerlinTerrainGenerator ptg2(4);
        ptg2.setParameters(params2);
        
        Heightmap result1 = ptg1.generate(expected_size);
        Heightmap result2 = ptg2.generate(expected_size);

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

    SECTION("Parameters maintain seed independence") {
        Vector2<int> expected_size(512, 512);

        PerlinParameters params;
        params.scale = 1.0f;
        params.cellSize = 32;
        params.gridSize = expected_size;

        // Use different seeds to verify seed independence
        PerlinTerrainGenerator ptg1(4);
        ptg1.setParameters(params);
        
        PerlinTerrainGenerator ptg2(8);
        ptg2.setParameters(params);

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
}

TEST_CASE("Diamond Square generator", "[diamond-square]")
{
    SECTION("Produces correct output within range") {
        Vector2<int> expected_size(512, 512);
        DiamondSquareParameters params;
        params.gridSize = expected_size;
        params.roughness = 1.0;

        DiamondSquareGenerator dsg(42);
        dsg.setParameters(params);
        Heightmap result = dsg.generate(params.gridSize);

        REQUIRE(result.size() == expected_size.x);
        for (int x = 0; x < expected_size.x; x++) {
            REQUIRE(result.at(0).size() == expected_size.y);
            for(int y = 0; y < expected_size.y; y++) {
                auto val = result.at(x)[y];
                REQUIRE(val >= -1);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different seeds produce different results") {
        Vector2<int> expected_size(64, 64);
        DiamondSquareParameters params;
        params.gridSize = expected_size;
        params.roughness = 1.0;

        DiamondSquareGenerator dsg1(42);
        dsg1.setParameters(params);
        DiamondSquareGenerator dsg2(84);
        dsg2.setParameters(params);

        Heightmap result1 = dsg1.generate(expected_size);
        Heightmap result2 = dsg2.generate(expected_size);

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