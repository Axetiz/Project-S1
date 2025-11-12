// OrbitSimLite - Renderer implementation (SFML)
#include "renderer.hpp"

#include <cmath>

namespace orbitsimlite {

Renderer::Renderer(unsigned width, unsigned height, double meters_to_pixels)
    : width_(width), height_(height), scale_(meters_to_pixels) {}

sf::Vector2f Renderer::world_to_screen(const Vec2& p) const {
    // Place world origin at screen center, +y upwards (SFML y is downwards)
    float cx = static_cast<float>(width_ / 2.0);
    float cy = static_cast<float>(height_ / 2.0);
    float x = static_cast<float>(meters_to_pixels(p.x, scale_));
    float y = static_cast<float>(meters_to_pixels(p.y, scale_));
    return sf::Vector2f{cx + x, cy - y};
}

void Renderer::rebuild_trails(std::size_t count) {
    trails_.clear();
    trails_.resize(count);
}

void Renderer::run(Simulator& sim) {
    sf::RenderWindow window(sf::VideoMode(width_, height_), "OrbitSimLite");
    window.setFramerateLimit(60);

    // Capture initial bodies for reset
    const std::vector<Body> initial_bodies = sim.get_bodies();
    rebuild_trails(initial_bodies.size());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    paused_ = !paused_;
                } else if (event.key.code == sf::Keyboard::R) {
                    sim.set_bodies(initial_bodies);
                    rebuild_trails(initial_bodies.size());
                }
            }
        }

        // Step simulation
        if (!paused_) {
            sim.step();
        }

        // Draw
        window.clear(sf::Color(10, 10, 20));

        const auto& bodies = sim.get_bodies();
        if (trails_.size() != bodies.size()) {
            rebuild_trails(bodies.size());
        }

        // Draw trails first
        for (std::size_t i = 0; i < bodies.size(); ++i) {
            const auto& b = bodies[i];
            auto screenPos = world_to_screen(b.pos);

            // Update trail
            auto& trail = trails_[i];
            trail.push_back(screenPos);
            if (trail.size() > max_trail_) trail.pop_front();

            // Convert color
            std::uint8_t r, g, bl;
            unpack_rgb(b.color, r, g, bl);
            sf::Color c(r, g, bl, 180);

            // Draw trail as line strip
            if (trail.size() >= 2) {
                sf::VertexArray lines(sf::LineStrip, trail.size());
                std::size_t idx = 0;
                for (const auto& tp : trail) {
                    lines[idx].position = tp;
                    // Fade older segments
                    float t = static_cast<float>(idx) / static_cast<float>(trail.size());
                    lines[idx].color = sf::Color(c.r, c.g, c.b, static_cast<sf::Uint8>(50 + 200 * t));
                    ++idx;
                }
                window.draw(lines);
            }
        }

        // Draw bodies on top
        for (const auto& b : bodies) {
            sf::CircleShape circle(static_cast<float>(b.radius));
            std::uint8_t r, g, bl;
            unpack_rgb(b.color, r, g, bl);
            circle.setFillColor(sf::Color(r, g, bl));
            auto p = world_to_screen(b.pos);
            circle.setPosition(p.x - circle.getRadius(), p.y - circle.getRadius());
            window.draw(circle);
        }

        window.display();
    }
}

} // namespace orbitsimlite

