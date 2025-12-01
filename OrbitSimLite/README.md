# OrbitSimLite

OrbitSimLite is a small C++17 project for experimenting with 2D Newtonian orbits. It consists of a reusable simulation/renderer library and a couple of example demos (solar system + binary stars) built on top of SFML.

## What it does

- Simulates point-mass bodies under Newtonian gravity in 2D (SI units, double precision).
- Supports two integrators: symplectic Euler and a simple RK4 step.
- Handles basic collision rules:
  - planet–planet collisions: pause + option to remove the lighter body,
  - body–star collisions: non‑star body is removed immediately,
  - natural satellites can be exempted from some collision rules.
- Renders bodies as circles with fading trails in an SFML window.
- Continuously exports the **current** simulation state to `bodies.json` (no history), including named bodies and kinematic data.
- Provides two demos:
  - `demo`: Sun–Mercury–Venus–Earth–Moon–Mars + one experimental planet.
  - `demo_two_suns`: two equal‑mass stars orbiting their common barycenter.

## Requirements

- C++17 compiler (GCC, Clang, or MSVC).
- CMake ≥ 3.15.
- SFML ≥ 2.5 (`system`, `window`, `graphics` components).

On Debian/Ubuntu (example):

```bash
sudo apt install libsfml-dev cmake build-essential
```

## Building

From the project root (where `CMakeLists.txt` lives):

```bash
mkdir -p build
cd build
cmake .. -DORBITSIMLITE_BUILD_DEMO=ON
cmake --build . --config Release
```

This builds:

- static library `liborbitsimlite.a`,
- demo executables `demo` and `demo_two_suns`.

## Running the demos

From the `build` directory:

```bash
./demo          # solar system style demo
./demo_two_suns # two‑suns binary orbit demo
```

Both demos ask for a time‑step multiplier on startup (scales the base dt used by the integrator).

### Controls (both demos)

- `SPACE` – pause/resume simulation.
- `R` – reset bodies to initial configuration and reset simulated time.
- `ESC` – exit.
- `C` – when a planet–planet collision is detected, remove the lighter body and continue.

The window title displays the accumulated simulated time in **Earth years**. The view auto‑adjusts on resize so circles remain round (no stretching into ovals).

## JSON output

Each frame the renderer writes a snapshot of the current bodies to `bodies.json` in the working directory (typically `build/` when running from there). The file contains only the latest state:

- per‑body name, mass, radius, packed colour,
- position, velocity, acceleration in SI units.

This is designed to be easy to consume from external tools/engines that want to drive logic based on a continuously changing set of physical parameters.

