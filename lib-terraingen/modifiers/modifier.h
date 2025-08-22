#pragma once
#include "terrain/terrain.h"

class Modifier {
public:
    explicit Modifier(Heightmap& heightmap) : heightmap(heightmap) {}
    virtual ~Modifier() = default;
    virtual void operate() = 0;

protected:
    Heightmap& heightmap;
};
