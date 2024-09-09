#include <fstream>

#include "boost/gil.hpp"
#include <boost/gil/extension/io/png.hpp>

#include "imageExporter.h"

void ImageExporter::saveToFile(const Heightmap &terrain, const std::string &filepath)
{
    boost::gil::gray16_image_t image(terrain.size(), terrain.at(0).size());
    auto image_view = boost::gil::view(image);
    for(int x=0; x<terrain.size(); x++)
    {
        for(auto &y: terrain.at(x))
        {
            image_view(x,y) = boost::gil::gray16_pixel_t(y);
        }
    }

    boost::gil::write_view(filepath, image_view, boost::gil::png_tag());
}