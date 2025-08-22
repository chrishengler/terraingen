#pragma once
#include "data_types.h"
#include "generatorParameters.h"
#include "generatorTypes.h"

struct GuiState {
    GeneratorType selectedType = GeneratorType::PERLIN;
    Vector2<int> gridSize = {256, 256};
    unsigned int seed = 0;
    PerlinParameters perlinParams;
    FlatParameters flatParams;
    bool generateRequested = false;
};