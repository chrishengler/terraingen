#include <fstream>

#include "boost/gil.hpp"
#include <boost/gil/extension/io/png.hpp>

#include "imageExporter.h"

using namespace boost::gil;

template <typename Image>
double get_max_value(Image& image) {
    return 1.0;
}

void ImageExporter::saveToFile(const Heightmap &terrain, const std::string &filepath)
{
    boost::gil::gray16_image_t image(terrain.size(), terrain.at(0).size());
    auto image_view = boost::gil::view(image);
    
    using pixel_t = decltype(image_view)::value_type;
    using channel_t = boost::gil::channel_type<pixel_t>::type;
    auto max_pixel_value = boost::gil::channel_traits<channel_t>::max_value();

    for(int x=0; x<terrain.size(); x++)
    {
        for(auto y=0; y<terrain[x].size(); y++)
        {
            image_view(x,y) = boost::gil::gray16_pixel_t(terrain[x][y] * max_pixel_value);
        }
    }

    boost::gil::write_view(filepath, image_view, boost::gil::png_tag());
}