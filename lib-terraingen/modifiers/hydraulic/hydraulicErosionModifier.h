#pragma once
#include <memory>
#include <random>
#include "particle.h"

namespace tg {
    namespace modify {
        struct HydraulicErosionParameters {
            unsigned int numParticles = 5000;          // Number of particles to simulate
            float inertia = 0.7f;                      // How much velocity is retained between steps
            float gravity = 9.81f;                     // Gravitational constant for acceleration
            float sedimentCapacity = 0.1f;             // Maximum sediment a particle can carry
            float depositionRate = 0.1f;               // Rate at which sediment is deposited
            float erosionRate = 0.1f;                  // Rate at which erosion occurs
            unsigned int numSteps = 100;               // Number of simulation steps per particle
        };

        std::unique_ptr<HydraulicErosionParameters> build_hydraulic_erosion_parameters(
            unsigned int numParticles,
            float inertia,
            float gravity,
            float sedimentCapacity,
            float depositionRate,
            float erosionRate,
            unsigned int numSteps
        );

        std::unique_ptr<Heightmap> applyHydraulicErosion(const std::unique_ptr<Heightmap> &hm, const HydraulicErosionParameters &params);

        class HydraulicErosionModifier{
        public:
            explicit HydraulicErosionModifier(Heightmap& heightmap);
            void operate();
            void setParameters(const HydraulicErosionParameters& params) {
                this->params = params;
            }

        private:
            Heightmap heightmap;
            HydraulicErosionParameters params;
            Vector2<double> calculateGradient(const Vector2<double>& pos);
            void simulateParticle(Particle& particle);
            bool isInBounds(const Vector2<double>& pos) const;
            double getInterpolatedHeight(const Vector2<double>& pos) const;
            void deposit(const Vector2<double>& pos, double amount);
            void erode(const Vector2<double>& pos, double amount);

            std::mt19937 rng;
        };
    }
}
