#include "data_types.h"
#include "external/lodepng/lodepng.h"
#include "external/stb/stb_image_write.h"
#include "imageExporter.h"

template <typename Image>
double get_max_value(Image& image) {
    return 1.0;
}

namespace tg {
    namespace imgexport {
        // for now just does pngs with 0 - 255
        void savePng8(const Heightmap &terrain, const std::string &filepath)
        {
            auto flattened_heightmap = flatten_heightmap_uchar(terrain);
            auto dims = getDimensions(terrain);
            stbi_write_png(filepath.c_str(), dims.x, dims.y, 1, flattened_heightmap.data(), 0);
        }

        void savePng16(const Heightmap &terrain, const std::string &filepath)
        {
            auto flattened_heightmap = flatten_heightmap_16bit(terrain);
            auto dims = getDimensions(terrain);
            auto error = lodepng::encode(filepath, flattened_heightmap.data(), dims.x, dims.y, LCT_GREY, 16);
        }

        void saveToFile(const std::unique_ptr<Heightmap> &terrain, const std::string &filepath, const ExportType &expType){
            switch(expType){
                case ExportType::PNG_8:
                    savePng8(*terrain, filepath);
                    break;
                case ExportType::PNG_16:
                    savePng16(*terrain, filepath);
                    break;
                }
        }
    }
}