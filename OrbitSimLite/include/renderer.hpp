// OrbitSimLite - SFML-based renderer
#pragma once

#include <deque>
#include <vector>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include "simulator.hpp"
#include "utils.hpp"

namespace orbitsimlite {

class Renderer {
public:
    Renderer(unsigned width = 1000, unsigned height = 800, double meters_to_pixels = 2e-9);

    // Runs the visualization loop. Blocks until window close.
    void run(Simulator& sim);

private:
    sf::Vector2f world_to_screen(const Vec2& p) const;
    void rebuild_trails(std::size_t count);

    unsigned width_;
    unsigned height_;
    double scale_; // meters to pixels
    bool paused_ {false};
    const std::size_t max_trail_ = 200;

    std::vector<std::deque<sf::Vector2f>> trails_;
};

} // namespace orbitsimlite