// OrbitSimLite - Demo application
#include <cstdint>
#include "simulator.hpp"
#include "renderer.hpp"
#include "utils.hpp"

using namespace orbitsimlite;

int main() {
    // Create simulator: G in SI, dt = 3600s (1 hour per step)
    Simulator sim(Physics::DefaultG, 36000.0, Integrator::RK4);

    // Bodies
    // Sun
    Body sun(1.989e30, Vec2{0.0, 0.0}, Vec2{0.0, 0.0}, 30.0, rgb_u32(255, 255, 0));
    sim.add_body(sun);

    // Earth
    Body earth(5.972e24, Vec2{1.496e11, 0.0}, Vec2{0.0, 29783.0}, 10.0, rgb_u32(70, 120, 255));
    sim.add_body(earth);

    // Venus
    Body venus(4.867e24, Vec2{1.082e11, 0.0}, Vec2{0.0, 35020.0}, 9.0, rgb_u32(255, 200, 120));
    sim.add_body(venus);

    //EX?
    Body ex(4.867e24, Vec2{1.082e11, 0.0}, Vec2{0.0, 35020.0}, 9.0, rgb_u32(255, 200, 120));
    sim.add_body(ex);

    // Renderer
    Renderer renderer(1000, 800, 2e-9);
    renderer.run(sim);

    return 0;
}
