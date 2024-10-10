#include "catch2/catch_test_macros.hpp"

#include "terrain/terrain.h"

TEST_CASE("Terrain")
{
    SECTION("Constructing by size")
    {
        Terrain terrain = Terrain(256, 128);
        REQUIRE(terrain.getSizeX() == 256);
        REQUIRE(terrain.getSizeY() == 128);

        Heightmap prepared_heightmap = terrain.getTerrain();
        REQUIRE(prepared_heightmap.capacity() == 256);
        for (auto row : prepared_heightmap)
        {
            REQUIRE(row.size() == 128);
        }
    }

    SECTION("Constructing from data")
    {
        std::valarray<double> row_1{0, 0.5};
        std::valarray<double> row_2{0.5, 1};
        Heightmap heightmap_initial_data = {row_1, row_2};

        Terrain terrain = Terrain(heightmap_initial_data);
        Heightmap heightmap = terrain.getTerrain();

        REQUIRE(heightmap.capacity() >= 2);
        for(auto row: heightmap)
        {
            REQUIRE(row.size() == 2);
        }
        REQUIRE(heightmap.at(0)[0] == 0);
        REQUIRE(heightmap.at(0)[1] == 0.5);
        REQUIRE(heightmap.at(1)[0] == 0.5);
        REQUIRE(heightmap.at(1)[1] == 1);
    }
}