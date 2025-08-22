#pragma once
#include "data_types.h"

class Modifier {
public:
    explicit Modifier(Heightmap& heightmap) : heightmap(heightmap) {}
    virtual ~Modifier() = default;
    virtual void operate() = 0;

protected:
    Heightmap& heightmap;
};
