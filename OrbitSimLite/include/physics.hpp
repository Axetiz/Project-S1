// OrbitSimLite - Physics utilities (gravity + integrators)
#pragma once

#include <vector>
#include "body.hpp"

namespace orbitsimlite {

struct Physics {
    static constexpr double DefaultG = 6.674e-11; // SI units

    // Gravitational acceleration on target due to others.
    static Vec2 acceleration(const Body& target, const std::vector<Body>& others, double G = DefaultG);

    // Simple symplectic Euler step: updates velocity then position.
    static void step_euler(Body& body, const Vec2& acc, double dt);

    // RK4 step for a single body, using others at their current positions.
    // This is an educational simplification of true N-body RK4.
    static void step_rk4(Body& body, const std::vector<Body>& others, double G, double dt);
};

} // namespace orbitsimlite