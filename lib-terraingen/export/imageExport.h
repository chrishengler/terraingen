#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "data_types.h"

namespace tg{
    namespace imgexport {
        enum class ExportType : uint8_t {
            PNG_8,
            PNG_16,
        };

        std::unique_ptr<std::vector<float>> flattenHeightmap(const Heightmap& hm);
        std::vector<unsigned char> flatten_heightmap_uchar(const Heightmap& hm);
        std::vector<unsigned char> flatten_heightmap_16bit(const Heightmap& hm);

        void savePng8(const Heightmap &terrain, const std::string &filepath);
        void savePng16(const Heightmap &terrain, const std::string &filepath);
        void saveToFile(const std::unique_ptr<Heightmap> &terrain, const std::string &filepath, const ExportType &exportType);
    }
}
