#include "hydraulicErosionModifier.h"
#include <random>
#include <algorithm>

HydraulicErosionModifier::HydraulicErosionModifier(Heightmap& heightmap)
    : Modifier(heightmap), rng(std::mt19937())
{
    rng.seed(std::time(0));
}

Vector2<double> HydraulicErosionModifier::calculateGradient(const Vector2<double>& pos) {
    int x = static_cast<int>(pos.x);
    int y = static_cast<int>(pos.y);
    Vector2<double> gradient{0.0, 0.0};
    
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if(dx == 0 && dy == 0) continue;
            
            int nx = x + dx;
            int ny = y + dy;
            
            if(nx >= 0 && nx < heightmap.size() && ny >= 0 && ny < heightmap[0].size()) {
                double heightDiff = heightmap[x][y] - heightmap[nx][ny];
                gradient.x += heightDiff * dx;
                gradient.y += heightDiff * dy;
            }
        }
    }
    
    // Normalize gradient
    double length = std::sqrt(gradient.x * gradient.x + gradient.y * gradient.y);
    if(length > 0) {
        gradient.x /= length;
        gradient.y /= length;
    }
    
    return gradient;
}

bool HydraulicErosionModifier::isInBounds(const Vector2<double>& pos) const {
    return pos.x >= 0 && pos.x < heightmap.size() - 1 &&
           pos.y >= 0 && pos.y < heightmap[0].size() - 1;
}

double HydraulicErosionModifier::getInterpolatedHeight(const Vector2<double>& pos) const {
    int x0 = static_cast<int>(pos.x);
    int y0 = static_cast<int>(pos.y);
    double fx = pos.x - x0;
    double fy = pos.y - y0;
    
    // Bilinear interpolation
    double h00 = heightmap[x0][y0];
    double h10 = heightmap[x0 + 1][y0];
    double h01 = heightmap[x0][y0 + 1];
    double h11 = heightmap[x0 + 1][y0 + 1];
    
    return h00 * (1 - fx) * (1 - fy) +
           h10 * fx * (1 - fy) +
           h01 * (1 - fx) * fy +
           h11 * fx * fy;
}

void HydraulicErosionModifier::deposit(const Vector2<double>& pos, double amount) {
    int x0 = static_cast<int>(pos.x);
    int y0 = static_cast<int>(pos.y);
    double fx = pos.x - x0;
    double fy = pos.y - y0;
    
    // Distribute sediment using bilinear interpolation weights
    heightmap[x0][y0] += amount * (1 - fx) * (1 - fy);
    heightmap[x0 + 1][y0] += amount * fx * (1 - fy);
    heightmap[x0][y0 + 1] += amount * (1 - fx) * fy;
    heightmap[x0 + 1][y0 + 1] += amount * fx * fy;
}

void HydraulicErosionModifier::erode(const Vector2<double>& pos, double amount) {
    deposit(pos, -amount);  // Erosion is just negative deposition
}

void HydraulicErosionModifier::simulateParticle(Particle& particle) {
    while(particle.lifetime > 0 && isInBounds(particle.position)) {
        // Calculate gradient at current position
        Vector2<double> gradient = calculateGradient(particle.position);
        
        // Update velocity with inertia and gradient influence
        particle.velocity.x = particle.velocity.x * params.inertia + gradient.x * params.gravity * (1 - params.inertia);
        particle.velocity.y = particle.velocity.y * params.inertia + gradient.y * params.gravity * (1 - params.inertia);
        
        // Add small random variation to velocity
        std::uniform_real_distribution<double> dist(-0.1, 0.1);
        particle.velocity.x += dist(rng);
        particle.velocity.y += dist(rng);

        // Move one square per step to avoid 'ghosting'
        auto normalisedVelocity = particle.velocity.normalised();

        // Move particle
        Vector2<double> newPos = particle.position + normalisedVelocity;       
        if(!isInBounds(newPos)) break;
        
        // Calculate height difference
        double oldHeight = getInterpolatedHeight(particle.position);
        double newHeight = getInterpolatedHeight(newPos);
        double heightDiff = newHeight - oldHeight;
       
        // Calculate sediment capacity based on velocity
        double speed = std::sqrt(particle.velocity.x * particle.velocity.x + 
                               particle.velocity.y * particle.velocity.y);
        double capacity = std::max(speed * params.sedimentCapacity, 0.01);
        
        if(heightDiff > 0) {
            // Moving uphill - deposit sediment
            double deposit = std::min(heightDiff, particle.sediment);
            particle.sediment -= deposit;
            this->deposit(particle.position, deposit);
        } else {
            // Moving downhill - erode and pick up sediment
            double erosion = std::min(capacity - particle.sediment, -heightDiff * params.erosionRate);
            if(erosion > 0) {
                this->erode(particle.position, erosion);
                particle.sediment += erosion;
            }
        }

        // Update particle position
        particle.position = newPos;
        
        particle.lifetime--;
    }
}

void HydraulicErosionModifier::operate() {
    std::uniform_real_distribution<double> distX(0, heightmap.size() - 1);
    std::uniform_real_distribution<double> distY(0, heightmap[0].size() - 1);
    
    // Simulate particles
    for(int i = 0; i < params.numParticles; i++) {
        Vector2<double> startPos{distX(rng), distY(rng)};
        Particle particle(startPos, params.numSteps);
        simulateParticle(particle);
    }
}
