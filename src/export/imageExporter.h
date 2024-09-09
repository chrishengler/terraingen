#pragma once
#include "data_types.h"

class ImageExporter
{
public:
    ImageExporter() {}

    void saveToFile(const Heightmap &terrain, const std::string &filepath);
};