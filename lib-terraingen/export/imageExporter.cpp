#include "data_types.h"
#include "external/lodepng/lodepng.h"
#include "external/stb/stb_image_write.h"
#include "imageExporter.h"

namespace tg {
    namespace imgexport {

        std::unique_ptr<std::vector<float>> flattenHeightmap(const Heightmap& hm) {
            std::vector<float> pixels;
            size_t rows = hm.size();
            size_t cols = hm.empty() ? 0 : hm[0].size();
            pixels.reserve(rows * cols);
            for (const auto& row : hm)
            for (double v : row) {
                pixels.push_back(static_cast<float>(v));
            }
            return std::make_unique<std::vector<float>>(pixels);
        }

        std::vector<unsigned char> flatten_heightmap_uchar(const Heightmap& hm){
            std::vector<unsigned char> pixels;
            size_t rows = hm.size();
            size_t cols = hm.empty() ? 0 : hm[0].size();
            pixels.reserve(rows * cols);
            for (const auto& row : hm)
            for (auto &v : row) {
                pixels.push_back(static_cast<unsigned char>(std::clamp(v*255, 0.0, 255.0)));
            }
            return pixels;
        }

        // for lodepng which works with raw buffers, so for 16 bit we have two unsigned chars (big-endian)
        std::vector<unsigned char> flatten_heightmap_16bit(const Heightmap& hm){
            std::vector<unsigned char> pixels;
            size_t rows = hm.size();
            size_t cols = hm.empty() ? 0 : hm[0].size();
            pixels.reserve(rows * cols * 2);
            for (const auto& row : hm)
            for (auto &v : row) {
                auto value = static_cast<int>(v*UINT16_MAX);
                value = static_cast<uint16_t>(std::clamp(value, 0, static_cast<int>(UINT16_MAX)));
                pixels.push_back(static_cast<unsigned char>((value >> 8) & 0xFF));
                pixels.push_back(static_cast<unsigned char>(value & 0xFF));
            }
            return pixels;
        }
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