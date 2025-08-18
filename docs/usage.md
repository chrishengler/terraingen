# Usage Guide

TerrainGen provides a simple interface for generating terrain heightmaps. This guide covers the basic usage of the library.

## Basic Usage

TerrainGen uses a factory pattern to create terrain generators. Here's a basic example:

```cpp
#include "generation/generatorFactory.h"
#include "export/imageExporter.h"

// Create a generator factory
GeneratorFactory factory;

// Create a Perlin noise generator with a random seed
auto generator = factory.createGenerator(12345, GeneratorType::PERLIN);

// Generate a 512x512 heightmap
Vector2<int> dimensions{512, 512};
auto heightmap = generator.generate(dimensions);

// Export the heightmap as a PNG
ImageExporter exporter;
exporter.saveToFile(heightmap, "terrain.png");
```

## Generator Types

Currently, TerrainGen supports three types of generators:

1. **Flat Terrain** (`GeneratorType::FLAT`)
   - Creates a uniform height terrain
   - Useful for testing and as a base for further modifications

2. **Perlin Noise** (`GeneratorType::PERLIN`)
   - Generates natural-looking terrain using Perlin noise
   - Creates smooth, continuous height variations

3. **Diamond Square** (`GeneratorType::DIAMOND_SQUARE`)
   - Generates natural-looking terrain using the Diamond-Square algorithm
   - Creates smooth, continuous height variations

## Combination

TerrainGen supports weighted addition of multiple terrains.

## Output Format

TerrainGen exports heightmaps as grayscale PNG images where:
- Black (0) represents the lowest elevation
- White (255) represents the highest elevation

These heightmaps can be used as input for 3D modeling software or further processed for game development.

Other output types are planned for future, including specific output formats targetting games 
which allow for importing custom maps.