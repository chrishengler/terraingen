#pragma once
#include "data_types.h"
#include "generatorParameters.h"
#include "generatorTypes.h"

struct GuiState {
    GeneratorType selectedType = GeneratorType::PERLIN;
    Vector2<unsigned int> gridSize = {256, 256};
    unsigned int seed = 0;
    DiamondSquareParameters diamondSquareParams;
    FlatParameters flatParams;
    PerlinParameters perlinParams;
    bool generateRequested = false;
    bool modifyRequested = false;
    Heightmap currentHeightmap;
};