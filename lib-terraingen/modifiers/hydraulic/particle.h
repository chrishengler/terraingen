#pragma once
#include "data_types.h"

class Particle {
public:
    Particle(Vector2<double> pos, int numSteps = 100) 
        : position(pos), velocity{0.0, 0.0}, sediment(0.0), lifetime(numSteps) {}

    Vector2<double> position;  // Continuous position on the heightmap
    Vector2<double> velocity;  // Current velocity vector
    double sediment;          // Amount of sediment being carried
    int lifetime;             // Remaining simulation steps
};
