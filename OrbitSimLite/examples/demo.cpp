// OrbitSimLite - Demo application
#include <cstdint>
#include <iostream>
#include "simulator.hpp"
#include "renderer.hpp"
#include "utils.hpp"

using namespace orbitsimlite;

int main() {
    // Create simulator: G in SI, dt = 3600s (1 hour per step)
    double multiplier = 1;
    std::cout<<"Enter standard simulator speed multiplier: ";
    std::cin>>multiplier;
    
    Simulator sim(Physics::DefaultG, 36000.0 * multiplier, Integrator::RK4);
    sim.set_substeps(12); // 12 substeps -> 300s internal step for stability

    // Bodies//

    // Sun
    Body sun(1.989e30, Vec2{0.0, 0.0}, Vec2{0.0, 0.0}, 30.0, rgb_u32(255, 255, 0));
    sim.add_body(sun);

    // Mercury
    Body mercury(3.301e23, Vec2{5.79e10, 0.0}, Vec2{0.0, 47360.0}, 6.0, rgb_u32(180, 180, 180));
    sim.add_body(mercury);

    // Venus
    Body venus(4.867e24, Vec2{1.082e11, 0.0}, Vec2{0.0, 35020.0}, 9.0, rgb_u32(255, 200, 120));
    sim.add_body(venus);

    //Experemental
    Body blop(4.857e23, Vec2{1e11, 0.0}, Vec2{0.0, 10000}, 9.0, rgb_u32(0,250,0));
    sim.add_body(blop);

    // Earth
    Body earth(5.972e24, Vec2{1.496e11, 0.0}, Vec2{0.0, 29783.0}, 10.0, rgb_u32(70, 120, 255));
    sim.add_body(earth);

    // Moon (bind to Earth; 90 degrees off the Sun line, prograde)
    Body moon(
        7.35e22,
        earth.pos + Vec2{0.0, 3.84e8},            // 384,000 km north of Earth
        earth.vel + Vec2{-1022.0, 0.0},           // 1.022 km/s west relative to Earth
        5.0,
        rgb_u32(200, 200, 200)
    );
    sim.add_body(moon);

    // Mars
    Body mars(6.417e23, Vec2{2.279e11, 0.0}, Vec2{0.0, 24077.0}, 7.0, rgb_u32(255, 100, 80));
    sim.add_body(mars);

    // Renderer
    Renderer renderer(1000, 800, 2e-9);
    renderer.run(sim);

    return 0;
}