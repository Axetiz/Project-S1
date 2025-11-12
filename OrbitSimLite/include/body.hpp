// OrbitSimLite - Body definition
#pragma once

#include <cstdint>
#include "vec2.hpp"

namespace orbitsimlite {

struct Body {
    double mass;
    double radius; // in pixels for rendering convenience
    Vec2 pos;      // meters
    Vec2 vel;      // meters/second
    Vec2 acc;      // meters/second^2 (updated each step)
    std::uint32_t color; // 0xRRGGBB

    Body();
    Body(double mass_, const Vec2& pos_, const Vec2& vel_, double radius_, std::uint32_t color_);
};

} // namespace orbitsimlite

