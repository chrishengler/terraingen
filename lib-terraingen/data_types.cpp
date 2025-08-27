#include "data_types.h"

std::vector<float> flattenHeightmap(const Heightmap& hm) {
    std::vector<float> pixels;
    if (hm.empty() || hm[0].size() == 0) return pixels;

    size_t width = hm.size();
    size_t height = hm[0].size();
    pixels.reserve(width * height);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            pixels.push_back(static_cast<float>(hm[x][y]));
        }
    }
    return pixels;
}