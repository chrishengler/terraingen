# Getting Started with TerrainGen

This guide will help you get up and running with TerrainGen for generating procedural terrain heightmaps.

## Installation

1. First, ensure you have all required dependencies installed:
   - CMake 3.10 or higher
   - A C++ compiler supporting C++11 or later
   - Catch2 (for running tests)

2. Clone the repository:
   ```bash
   git clone https://github.com/chrishengler/terraingen.git
   cd terraingen
   ```

3. Create a build directory and compile:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Verifying Installation

After building, you can run the test suite to verify everything is working correctly:

```bash
cd build/test
./tests
```

All tests should pass. If you encounter any failures, please check that all dependencies are correctly installed and that your build environment is properly configured.
