#include "data_types.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb/stb_image_write.h"
#include "imageExporter.h"

template <typename Image>
double get_max_value(Image& image) {
    return 1.0;
}

// for now just does pngs with 0 - 255
void ImageExporter::saveToFile(const Heightmap &terrain, const std::string &filepath)
{
    auto flattened_heightmap = flatten_heightmap_uint(terrain, 255);
    auto dims = getDimensions(terrain);
    stbi_write_png(filepath.c_str(), dims.x, dims.y, 1, flattened_heightmap.data(), 0);
}