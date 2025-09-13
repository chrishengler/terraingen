
#include "catch2/catch_test_macros.hpp"

#include <filesystem>
#include "external/stb/stb_image.h"

#include "data_types.h"
#include "imageExporter.h"
#include "helpers/helpers.h"

unsigned char* load_greyscale_png_file(const std::string &filename, int cols, int rows){
    int channels_in_file = 1;
    return stbi_load(filename.c_str(), &cols, &rows, &channels_in_file, 0);
}

bool data_equals_heightmap(unsigned char *data, const Heightmap &hm, const float epsilon = 1){
    auto flattened_heightmap = flatten_heightmap_uint(hm, 255);
    for(unsigned int i = 0; i < flattened_heightmap.size(); i++){
        // assumes greyscale data, otherwise we'd have to account for number of channels
        int diff = static_cast<int>(data[i]) - static_cast<int>(flattened_heightmap[i]);
        if(std::abs(diff) > epsilon){
            return false;
        }
    }
    return true;
}

TEST_CASE("export png")
{
    SECTION("image exporter writes a file")
    {
        Heightmap testHeightmap;
        testHeightmap.push_back(std::valarray<double>(1));

        ImageExporter imgExporter;
        auto filepath = get_temp_filepath("png");
        imgExporter.saveToFile(testHeightmap, filepath.string());
        REQUIRE(fs::exists(filepath));
    }

    SECTION("exported image has correct data")
    {
        SECTION("all 0s")
        {
            Heightmap testHeightmap;
            for(int x=0; x<10; x++)
            {
                auto row = std::valarray<double>(10);
                testHeightmap.push_back(row);
            }

            ImageExporter imgExporter;
            auto filepath = get_temp_filepath("png");
            imgExporter.saveToFile(testHeightmap, filepath.string());
            REQUIRE(fs::exists(filepath));

            auto exampleFilepath = fs::current_path() / "data/black-10x10.png";
            REQUIRE(fs::exists(exampleFilepath));

            auto loadedImageData = load_greyscale_png_file(exampleFilepath, 10, 10);
            REQUIRE(data_equals_heightmap(loadedImageData, testHeightmap));
        }

        SECTION("all 1s")
        {
            Heightmap testHeightmap;
            for(int x=0; x<10; x++)
            {
                auto row = std::valarray<double>(10);
                for(unsigned int y=0; y<10; y++)
                {
                    row[y]=1;
                }
                testHeightmap.push_back(row);
            }

            ImageExporter imgExporter;
            auto filepath = get_temp_filepath("png");
            imgExporter.saveToFile(testHeightmap, filepath.string());
            REQUIRE(fs::exists(filepath));

            auto exampleFilepath = fs::current_path() / "data/white-10x10.png";
            REQUIRE(fs::exists(exampleFilepath));

            auto loadedImageData = load_greyscale_png_file(exampleFilepath, 10, 10);
            REQUIRE(data_equals_heightmap(loadedImageData, testHeightmap));
        }
    }
}
