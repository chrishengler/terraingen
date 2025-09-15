#include "catch2/catch_test_macros.hpp"

#include "data_types.h"
#include "generatorParameters.h"
#include "perlin/perlin.h"
#include "diamondSquare/diamondSquare.h"

TEST_CASE("Generator Tests", "[generator]")
{
    SECTION("Perlin noise generator can be created with seed and parameters")
    {
        Vector2<uint32_t> gridSize(10, 10);
        PerlinParameters pp{gridSize.x, gridSize.y, 4, 2.0, 32};

        // Verify parameters by generating terrain and checking scale and grid size
        Heightmap result = tg::generate::generate_perlin(pp);
        REQUIRE(result.size() == gridSize.x);
        REQUIRE(result[0].size() == gridSize.y);
    }
}

TEST_CASE("Perlin generator parameters", "[perlin]")
{
    SECTION("Default scale produces output within range") {
        Vector2<uint32_t> expected_size(512, 512);
        
        PerlinParameters params{ expected_size.x, expected_size.y, 0};

        Heightmap result = tg::generate::generate_perlin(params);

        REQUIRE(result.size() == expected_size.x);  // Number of columns
        for (unsigned int col = 0; col < expected_size.x; col++) {
            REQUIRE(result.at(0).size() == expected_size.y);  // Number of rows
            for(unsigned int row = 0; row < expected_size.y; row++) {
                auto val = result.at(col)[row];
                REQUIRE(val >= 0);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different scales produce different results") {
        Vector2<uint32_t> expected_size(512, 512);

        PerlinParameters params1{
            expected_size.x, expected_size.y, 4, 1.0, 32,
        };

        PerlinParameters params2{
            expected_size.x, expected_size.y, 4, 2.0, 32,
        };

        Heightmap result1 = tg::generate::generate_perlin(params1);
        Heightmap result2 = tg::generate::generate_perlin(params2);

        bool found_different = false;
        for (unsigned int col = 0; col < expected_size.x && !found_different; col++) {
            for (unsigned int row = 0; row < expected_size.y && !found_different; row++) {
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
        Vector2<uint32_t> expected_size(512, 512);
        DiamondSquareParameters params{
            expected_size.x,
            expected_size.y,
            42,
            1.0
        };

        Heightmap result = tg::generate::generate_ds(params);

        REQUIRE(result.size() == expected_size.x);
        for (unsigned int x = 0; x < expected_size.x; x++) {
            REQUIRE(result.at(0).size() == expected_size.y);
            for(unsigned int y = 0; y < expected_size.y; y++) {
                auto val = result.at(x)[y];
                REQUIRE(val >= 0);
                REQUIRE(val <= 1);
            }
        }
    }

    SECTION("Different seeds produce different results") {
        Vector2<uint32_t> expected_size(64, 64);
        DiamondSquareParameters params
        {
            expected_size.x,
            expected_size.y,
            42,
            1.0
        };

        Heightmap result1 = tg::generate::generate_ds(params);

        params.seed = 84;
        Heightmap result2 = tg::generate::generate_ds(params);

        bool found_different = false;
        for (unsigned int x = 0; x < expected_size.x && !found_different; x++) {
            for (unsigned int y = 0; y < expected_size.y && !found_different; y++) {
                if (result1[x][y] != result2[x][y]) {
                    found_different = true;
                }
            }
        }
        REQUIRE(found_different);
    }
}