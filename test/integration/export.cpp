#include <filesystem>
#include "catch2/catch_test_macros.hpp"

#include "diamondsquare/diamondSquareGenerator.h"
#include "generatorParameters.h"
#include "perlin/perlinTerrainGenerator.h"
#include "imageExporter.h"

#include "helpers/helpers.h"

TEST_CASE("Perlin export")
{
    PerlinParameters pp{
        1.0f, 
        32
    };
    PerlinTerrainGenerator ptg;
    ptg.setParameters(pp);
    Vector2<uint> expected_size(2048,2048);
    Heightmap result = ptg.generate(expected_size, 0);

    ImageExporter imgExporter;
    auto filepath = get_temp_filepath("png", "perlin");
    imgExporter.saveToFile(result, filepath.string());
    REQUIRE(fs::exists(filepath));
}

TEST_CASE("Diamond Square export")
{
    Vector2<int> cell_sizes(256,256);
    DiamondSquareParameters dsp{1.0};
    DiamondSquareGenerator dsg;
    dsg.setParameters(dsp);
    Vector2<uint> expected_size(2048,2048);
    Heightmap result = dsg.generate(expected_size, 0);

    ImageExporter imgExporter;
    auto filepath = get_temp_filepath("png", "diamond-square");
    imgExporter.saveToFile(result, filepath.string());
    REQUIRE(fs::exists(filepath));
}