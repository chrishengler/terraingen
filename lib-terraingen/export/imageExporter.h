#pragma once
#include <string>

#include "data_types.h"

class ImageExporter
{
public:
    ImageExporter() {}

    void saveToFile(const Heightmap &terrain, const std::string &filepath);
};

void saveToFile(const std::unique_ptr<Heightmap> &terrain, const std::string &filepath);