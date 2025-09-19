# TerrainGen

TerrainGen is a C++ library for procedural terrain generation. It provides tools to create heightmaps using various algorithms, which can then be exported as image files.

## Quick Start

1. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. Run the tests to ensure everything is working:
   ```bash
   cd build/test
   ./tests
   ```

## Features

- Multiple terrain generation algorithms:
  - Flat terrain (useful for testing)
  - Perlin noise-based terrain
  - Additional techniques in future releases
- PNG export of generated heightmaps
- Configurable terrain dimensions
- Seeded generation for reproducible results

## Documentation

- [Getting Started](getting-started.md)
- [Usage Guide](usage.md)
- [Generation Algorithms](algorithms.md)

## Dependencies

- CMake (build system)
- Catch2 (for tests)
