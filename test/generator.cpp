#include <iostream>
#include "catch2/catch_test_macros.hpp"

#include "terrain/terrain.h"
#include "generation/flat/flatTerrainGenerator.h"

TEST_CASE("GENERATOR")
{
    SECTION("FLAT TERRAIN GENERATOR")
    {
        FlatTerrainGenerator ftg = FlatTerrainGenerator(0);
        Heightmap result = ftg.generate(2,3);

        REQUIRE(result.size() == 2);
        for(int x=0; x<2; x++)
        {
            REQUIRE(result.at(0).size() == 3);
            for(int y=0; y<3; y++)
            {
                REQUIRE(result.at(x).at(y) == 4);
            }
        }
    }
}