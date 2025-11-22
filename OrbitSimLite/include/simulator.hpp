// OrbitSimLite - Simulator orchestrating bodies and stepping
#pragma once

#include <vector>
#include "body.hpp"
#include "physics.hpp"

namespace orbitsimlite {

enum class Integrator { Euler, RK4 };

class Simulator {
public:
    explicit Simulator(double G = Physics::DefaultG, double dt = 1.0, Integrator integrator = Integrator::RK4);

    void add_body(const Body& b);
    void set_bodies(const std::vector<Body>& bs);
    void clear();

    void set_dt(double dt_);
    double get_dt() const;

    void set_integrator(Integrator i);
    Integrator get_integrator() const;

    void set_gravity(double G_);
    double get_gravity() const;

    // Substeps per call to step() for improved stability
    void set_substeps(int n);
    int get_substeps() const;

    // Advance the whole system by one step of size dt.
    void step();

    const std::vector<Body>& get_bodies() const;
    std::vector<Body>& access_bodies();

private:
    double G_;
    double dt_;
    Integrator integrator_;
    std::vector<Body> bodies_;
    int substeps_;
};

} // namespace orbitsimlite