#include <filesystem>
#include <sstream>
#include "catch2/catch_test_macros.hpp"

#include "perlin/perlinTerrainGenerator.h"
#include "imageExporter.h"

#include "helpers/helpers.h"

TEST_CASE("Perlin export")
{
    Vector2<int> cell_sizes(256,256);
    PerlinTerrainGenerator ptg(0, cell_sizes);
    Vector2<int> expected_size(2048,2048);
    Heightmap result = ptg.generate(expected_size);

    ImageExporter imgExporter;
    auto filepath = get_temp_filepath("png");
    imgExporter.saveToFile(result, filepath.string());
    REQUIRE(fs::exists(filepath));
}