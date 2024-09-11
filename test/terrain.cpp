#include <iostream>

#include "catch2/catch_test_macros.hpp"

#include "terrain/terrain.h"

TEST_CASE("Terrain")
{
    SECTION("Constructing by size")
    {
        Terrain terrain = Terrain(256, 128);
        REQUIRE(terrain.get_size_x() == 256);
        REQUIRE(terrain.get_size_y() == 128);

        Heightmap prepared_heightmap = terrain.get_terrain();
        REQUIRE(prepared_heightmap.capacity() == 256);
        for (auto row : prepared_heightmap)
        {
            REQUIRE(row.capacity() == 128);
        }
    }

    SECTION("Constructing from data")
    {
        std::vector<double> row_1{0, 0.5};
        std::vector<double> row_2{0.5, 1};
        std::vector<std::vector<double>> heightmap_initial_data = {row_1, row_2};

        Terrain terrain = Terrain(heightmap_initial_data);
        Heightmap heightmap = terrain.get_terrain();

        REQUIRE(heightmap.capacity() >= 2);
        for(auto row: heightmap)
        {
            REQUIRE(row.capacity() >= 2);
        }
        REQUIRE(heightmap.at(0).at(0) == 0);
        REQUIRE(heightmap.at(0).at(1) == 0.5);
        REQUIRE(heightmap.at(1).at(0) == 0.5);
        REQUIRE(heightmap.at(1).at(1) == 1);
    }
}