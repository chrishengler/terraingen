#include <iomanip>
#include <iostream>
#include "catch2/catch_test_macros.hpp"

#include "terrain/terrain.h"
#include "flat/flatTerrainGenerator.h"
#include "perlin/perlinTerrainGenerator.h"

TEST_CASE("FLAT TERRAIN GENERATOR")
{
    FlatTerrainGenerator ftg(0);
    Heightmap result = ftg.generate(Vector2<unsigned int>(2, 3));

    REQUIRE(result.size() == 2);
    for (int x = 0; x < 2; x++)
    {
        REQUIRE(result.at(0).size() == 3);
        for (int y = 0; y < 3; y++)
        {
            REQUIRE(result.at(x).at(y) == 4);
        }
    }
}

TEST_CASE("PERLIN GENERATOR")
{
    Vector2<unsigned int> cell_sizes(16,16);
    PerlinTerrainGenerator ptg(0, cell_sizes);
    Vector2<unsigned int> expected_size(64,64);
    Heightmap result = ptg.generate(expected_size);

    double max_abs_value = std::sqrt(2);
    REQUIRE(result.size() == expected_size.x);
    for (int x=0; x<expected_size.x; x++)
    {
        REQUIRE(result.at(0).size() == expected_size.y);
        for(int y = 0; y<expected_size.y; y++)
        {
            double abs_noise_value = std::abs((double)result.at(x).at(y));
            // REQUIRE(abs_noise_value <= max_abs_value);
            std::cout << std::setw(3) << result.at(x).at(y) << ",";
        }
        std::cout << std::endl;
    }
}