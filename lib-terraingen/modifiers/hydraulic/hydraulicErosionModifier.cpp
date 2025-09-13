#include <algorithm>
#include <ctime>
#include <random>

#include "hydraulicErosionModifier.h"

HydraulicErosionModifier::HydraulicErosionModifier(Heightmap& heightmap)
    : Modifier(heightmap), rng(std::mt19937())
{
    rng.seed((unsigned int)std::time(0));
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
        Vector2<double> gradient = calculateGradient(particle.position);
        particle.velocity.x = particle.velocity.x * params.inertia + gradient.x * params.gravity * (1 - params.inertia);
        particle.velocity.y = particle.velocity.y * params.inertia + gradient.y * params.gravity * (1 - params.inertia);
        
        std::uniform_real_distribution<double> dist(-0.1, 0.1);
        particle.velocity.x += dist(rng);
        particle.velocity.y += dist(rng);

        // Moving by velocity leads to weird artifacts from skipping squares,
        // Normalize to ensure no squares skipped
        auto normalisedVelocity = particle.velocity.normalised();
        Vector2<double> newPos = particle.position + normalisedVelocity;       
        if(!isInBounds(newPos)) break;
        
        double oldHeight = getInterpolatedHeight(particle.position);
        double newHeight = getInterpolatedHeight(newPos);
        double heightDiff = newHeight - oldHeight;
        
        if(heightDiff > 0) {
            double deposit = std::min(heightDiff, particle.sediment);
            particle.sediment -= deposit;
            this->deposit(particle.position, deposit);
        } else {
            double speed = particle.velocity.magnitude();
            double capacity = std::max(speed * params.sedimentCapacity, 0.01);

            double erosion = std::min(capacity - particle.sediment, -heightDiff * params.erosionRate);
            if(erosion > 0) {
                this->erode(particle.position, erosion);
                particle.sediment += erosion;
            }
        }

        particle.position = newPos;
        particle.lifetime--;
    }
}

void HydraulicErosionModifier::operate() {
    std::uniform_real_distribution<double> distX(0, (double)heightmap.size() - 1);
    std::uniform_real_distribution<double> distY(0, (double)heightmap[0].size() - 1);
    
    for(int i = 0; i < params.numParticles; i++) {
        Vector2<double> startPos{distX(rng), distY(rng)};
        Particle particle(startPos, params.numSteps);
        simulateParticle(particle);
    }
}
