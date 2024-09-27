#include "catch2/catch_test_macros.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>

#include "imageExporter.h"
#include "helpers/helpers.h"

namespace bg = boost::gil;

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

            bg::gray16_image_t exampleImage;
            bg::read_and_convert_image(exampleFilepath.string(), exampleImage, bg::png_tag());
            bg::gray16_image_t writtenImage;
            bg::read_and_convert_image(filepath.string(), writtenImage, bg::png_tag());
            REQUIRE(exampleImage == writtenImage);
        }

        SECTION("all 1s")
        {
            Heightmap testHeightmap;
            for(int x=0; x<10; x++)
            {
                auto row = std::valarray<double>(10);
                for(int y=0; y<10; y++)
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

            bg::gray16_image_t exampleImage;
            bg::read_and_convert_image(exampleFilepath.string(), exampleImage, bg::png_tag());
            bg::gray16_image_t writtenImage;
            bg::read_and_convert_image(filepath.string(), writtenImage, bg::png_tag());
            REQUIRE(exampleImage == writtenImage);
        }
    }
}
