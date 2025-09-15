#include <filesystem>
#include "catch2/catch_test_macros.hpp"

#include "diamondsquare/diamondSquare.h"
#include "generatorParameters.h"
#include "perlin/perlin.h"
#include "imageExport.h"

#include "helpers/helpers.h"

TEST_CASE("Perlin export")
{
    PerlinParameters pp{
        2048,
        2048,
        0,
        1.0f, 
        32
    };
    Vector2<uint32_t> expected_size(2048,2048);
    Heightmap result = tg::generate::generate_perlin(pp);

    auto filepath = get_temp_filepath("png", "perlin");
    tg::imgexport::savePng8(result, filepath.string());
    REQUIRE(fs::exists(filepath));
}

TEST_CASE("Diamond Square export")
{
    Vector2<int> cell_sizes(256,256);
    DiamondSquareParameters dsp{2048, 2048, 0, 1.0};
    Heightmap result = tg::generate::generate_ds(dsp);

    auto filepath = get_temp_filepath("png", "diamond-square");
    tg::imgexport::savePng8(result, filepath.string());
    REQUIRE(fs::exists(filepath));
}