#pragma once
#include "modifiers/modifier.h"

class HydraulicErosionModifier : public Modifier {
public:
    explicit HydraulicErosionModifier(Heightmap& heightmap);
    void operate() override;
};
