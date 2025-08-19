#include <boost/gil/extension/io/png.hpp>

#include "imageExporter.h"

namespace bg = boost::gil;

template <typename Image>
double get_max_value(Image& image) {
    return 1.0;
}

void ImageExporter::saveToFile(const Heightmap &terrain, const std::string &filepath)
{
    bg::gray16_image_t image(terrain.size(), terrain.at(0).size());
    auto image_view = bg::view(image);
    
    using pixel_t = decltype(image_view)::value_type;
    using channel_t = bg::channel_type<pixel_t>::type;
    auto max_pixel_value = bg::channel_traits<channel_t>::max_value();

    for(int x=0; x<terrain.size(); x++)
    {
        for(auto y=0; y<terrain[x].size(); y++)
        {
            image_view(x,y) = bg::gray16_pixel_t((uint16_t)(terrain[x][y] * max_pixel_value));
        }
    }

    bg::write_view(filepath, image_view, bg::png_tag());
}