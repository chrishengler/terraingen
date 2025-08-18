# Generation Algorithms

TerrainGen uses various algorithms to generate terrain heightmaps. Here's an overview of the currently implemented methods.

## Flat Terrain

The flat terrain generator creates a uniform heightmap where all points have the same elevation. While not particularly interesting for terrain generation, it serves several purposes:

- Testing and validation of the generation pipeline
- Creating base terrains for further modification
- As a control case when comparing different generation methods

## Perlin Noise

Perlin noise is one of the most widely-used methods for generating terrain. This algorithm, developed by Ken Perlin in 1983, creates smooth, continuous pseudo-random variations that can closely resemble natural terrain features.

### How Perlin Noise Works

Perlin noise works by:
1. Generating a grid of random gradient vectors
2. Computing interpolated values between these vectors
3. (Not yet implemented in TerrainGen) Combining multiple frequencies (octaves) of noise to create natural-looking variation

### Characteristics

- **Continuity**: The generated terrain is smooth and continuous, without sudden jumps in elevation
- **Reproducibility**: Using the same seed will always generate the same terrain
- **Natural Appearance**: The resulting heightmaps resemble natural terrain features like hills and valleys

### Parameters

The Perlin noise generator accepts a seed value that determines the random number sequence used to generate the terrain. Using the same seed will produce identical results, making it useful for:

- Debugging and testing
- Generating consistent terrain across different runs
- Sharing specific terrain configurations with others

## Diamond-Square Algorithm

The Diamond-Square algorithm (also known as the Midpoint-Displacement Algorithm) is a fractal-based method for generating heightmaps that creates realistic-looking terrain with both rough and smooth features.

### How Diamond-Square Works

The algorithm works by repeatedly subdividing a grid and calculating new height values:

1. Start with a grid where only the corner values are set
2. Diamond step: For each square in the grid, set the midpoint height to the average of the four corners plus a random value
3. Square step: For each diamond in the grid, set the midpoint height to the average of the four adjacent points plus a random value
4. Reduce the random variation amount and the step size by half
5. Repeat steps 2-4 until the entire grid is filled

### Characteristics

- **Fractal Nature**: Creates self-similar patterns at different scales
- **Natural Variation**: Produces terrain with both smooth gradients and rough features
- **Edge Continuity**: Creates continuous terrain without sharp discontinuities

### Parameters

The Diamond-Square generator accepts:
- A seed value for reproducible terrain generation
- Cell sizes that influence the scale of the terrain features

Like other generators in TerrainGen, the output is normalized to ensure height values fall between -1 and 1.

## Future Developments

Additional terrain generation techniques are planned for future releases, including:

- Erosion simulation
