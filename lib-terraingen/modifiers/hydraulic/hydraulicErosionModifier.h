#pragma once
#include "modifiers/modifier.h"
#include "particle.h"
#include <random>

struct HydraulicErosionParameters {
    int numParticles = 5000;          // Number of particles to simulate
    double inertia = 0.7;             // How much velocity is retained between steps
    double gravity = 9.81;            // Gravitational constant for acceleration
    double sedimentCapacity = 0.1;    // Maximum sediment a particle can carry
    double depositionRate = 0.1;      // Rate at which sediment is deposited
    double erosionRate = 0.1;         // Rate at which erosion occurs
    int numSteps = 100;               // Number of simulation steps per particle
};

class HydraulicErosionModifier : public Modifier {
public:
    explicit HydraulicErosionModifier(Heightmap& heightmap);
    void operate() override;
    void setParameters(const HydraulicErosionParameters& params) {
        this->params = params;
    }

private:
    HydraulicErosionParameters params;
    Vector2<double> calculateGradient(const Vector2<double>& pos);
    void simulateParticle(Particle& particle);
    bool isInBounds(const Vector2<double>& pos) const;
    double getInterpolatedHeight(const Vector2<double>& pos) const;
    void deposit(const Vector2<double>& pos, double amount);
    void erode(const Vector2<double>& pos, double amount);

    std::mt19937 rng;
};
