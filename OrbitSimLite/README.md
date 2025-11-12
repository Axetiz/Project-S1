# OrbitSimLite

OrbitSimLite is a small educational C++17 library and demo for simulating and visualizing simple 2D Newtonian orbits. It uses SI units (meters, kilograms, seconds) and SFML for rendering.

## Features
- Double-precision 2D vectors and bodies
- Newtonian gravity with configurable `G` (default `6.674e-11`)
- Two integrators: Symplectic Euler and RK4 (educational per-body RK4)
- Simple simulator managing a list of bodies and time stepping
- SFML renderer with trails and basic controls

## Project Layout
```
OrbitSimLite/
 ├── include/
 │    ├── vec2.hpp          // 2D vector math
 │    ├── body.hpp          // Body: mass, position, velocity, radius, color
 │    ├── physics.hpp       // Gravity + integrators (Euler + RK4)
 │    ├── simulator.hpp     // Manages bodies + simulation steps
 │    ├── renderer.hpp      // SFML-based 2D renderer
 │    └── utils.hpp         // Unit conversions, color helpers
 ├── src/
 │    ├── vec2.cpp
 │    ├── body.cpp
 │    ├── physics.cpp
 │    ├── simulator.cpp
 │    ├── renderer.cpp
 ├── examples/
 │    └── demo.cpp          // Demo application
 ├── CMakeLists.txt
 └── README.md
```

## Build Instructions
Prerequisites:
- A C++17 compiler (GCC, Clang, or MSVC)
- CMake 3.15+
- SFML 2.5+ (system, window, graphics)

On Debian/Ubuntu:
- `sudo apt install libsfml-dev cmake build-essential`

On macOS (Homebrew):
- `brew install sfml cmake`

Build:
```
mkdir build && cd build
cmake .. -DORBITSIMLITE_BUILD_DEMO=ON
cmake --build . --config Release
```
Run the demo executable from the build directory:
- Linux/macOS: `./demo`
- Windows (MSVC): `./Release/demo.exe`

## Example Usage
See `examples/demo.cpp` for a complete example that creates a Sun–Earth–Moon system:
- `G = 6.674e-11`
- `dt = 3600` seconds (1 hour per step)
- The renderer uses a 1000×800 window and draws bodies as circles with trails.

Switch integrators:
```
orbitsimlite::Simulator sim(orbitsimlite::Physics::DefaultG, 3600.0, orbitsimlite::Integrator::RK4);
sim.set_integrator(orbitsimlite::Integrator::Euler);
```

## Keyboard Controls
- SPACE: pause/resume
- R: reset bodies to initial demo configuration and clear trails
- ESC: exit

## Notes
- The RK4 implementation updates one body at a time using other bodies’ current positions for intermediate stages. This keeps the code simple and educational, but it’s an approximation of a full system RK4 integration.
- Distances are large; the renderer uses a constant meters-to-pixels scale (default `2e-9`) and places the origin at the window center with +Y up.

## Screenshot
(placeholder)

