#include "catch2/catch_test_macros.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>

#include "imageExporter.h"

std::filesystem::path get_temp_filepath(const std::string &extension)
{
        std::stringstream filename("");
        filename << "terraingen-test-export-" << std::rand() << "." << extension;
        auto filepath = std::filesystem::path(std::filesystem::temp_directory_path() / filename.str());

        WARN(filepath);
        return filepath;
}

TEST_CASE("export png")
{
    SECTION("image exporter writes a file")
    {
        Heightmap testHeightmap;
        testHeightmap.push_back(std::vector<unsigned int>(1));

        ImageExporter imgExporter;
        auto filepath = get_temp_filepath("png");
        imgExporter.saveToFile(testHeightmap, filepath);
        REQUIRE(std::filesystem::exists(filepath));
    }

    SECTION("exported image has correct data")
    {
        SECTION("all 0s")
        {
            Heightmap testHeightmap;
            for(int x=0; x<10; x++)
            {
                auto row = std::vector<unsigned int>(10);
                testHeightmap.push_back(row);
            }

            ImageExporter imgExporter;
            auto filepath = get_temp_filepath("png");
            imgExporter.saveToFile(testHeightmap, filepath);
            REQUIRE(std::filesystem::exists(filepath));

            auto exampleFilepath = std::filesystem::current_path() / "data/black-10x10.png";
            REQUIRE(std::filesystem::exists(exampleFilepath));

            boost::gil::gray16_image_t exampleImage;
            boost::gil::read_and_convert_image(exampleFilepath, exampleImage, boost::gil::png_tag());
            boost::gil::gray16_image_t writtenImage;
            boost::gil::read_and_convert_image(filepath, writtenImage, boost::gil::png_tag());
            REQUIRE(exampleImage == writtenImage);
        }

        SECTION("all 1s")
        {
            Heightmap testHeightmap;
            for(int x=0; x<10; x++)
            {
                auto row = std::vector<unsigned int>(10);
                for(int y=0; y<10; y++)
                {
                    row[y]=1;
                }
                testHeightmap.push_back(row);
            }

            ImageExporter imgExporter;
            auto filepath = get_temp_filepath("png");
            imgExporter.saveToFile(testHeightmap, filepath);
            REQUIRE(std::filesystem::exists(filepath));

            auto exampleFilepath = std::filesystem::current_path() / "data/black-10x10.png";
            REQUIRE(std::filesystem::exists(exampleFilepath));

            boost::gil::gray16_image_t exampleImage;
            boost::gil::read_and_convert_image(exampleFilepath, exampleImage, boost::gil::png_tag());
            boost::gil::gray16_image_t writtenImage;
            boost::gil::read_and_convert_image(filepath, writtenImage, boost::gil::png_tag());
            REQUIRE(exampleImage == writtenImage);

        }
    }


    std::ifstream expectedFile(std::filesystem::current_path().parent_path() / "test/data/black-10x10.png", std::ios::binary);

    REQUIRE(expectedFile.is_open());
}
