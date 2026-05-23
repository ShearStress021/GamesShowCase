# PebbleSort

A water-sort puzzle game clone — but with colored pebbles instead of water. Built with C++ and Raylib.

## Features

- **Sorting puzzle gameplay** — pour pebbles between tubes until each tube holds pebbles of a single color
- **Procedural level generation** — infinitely many guaranteed-solvable puzzles via reverse-shuffle
- **Variable difficulty** — tube capacity (3–5 pebbles) and number of colors scale as you progress
- **Hint system** — BFS solver shows the next optimal move
- **Undo & Reset** — reverse individual pours or restart the level
- **Pour animations** — smooth lerp-based pebble movement between tubes
- **Win animations** — celebratory tube glow and particles on completion
- **Level select** — unlocked progression through difficulty tiers

## Prerequisites

- C++17 compiler (GCC, Clang, or MSVC)
- [Raylib](https://www.raylib.com/) 5.0+
- CMake (optional, for the multi-file build variant)

## Build & Run

### Single-file build

```bash
g++ main.cpp -o pebbleSort -lraylib -lopengl32 -lgdi32 -lwinmm
./pebbleSort
```

### CMake build

```bash
mkdir build && cd build
cmake ..
cmake --build .
./pebbleSort
```

Raylib installation varies by platform. On Windows, the easiest path is to drop `raylib.dll` and headers alongside the source. On Linux/macOS, use your package manager or build from source.

## Usage

1. **Launch** the game — the menu screen appears
2. **Select a level** from the level-select grid
3. **Click a tube** to select it (highlighted border)
4. **Click another tube** to pour pebbles — all consecutive same-color pebbles at the top transfer if the destination has room
5. **Clear all tubes** (each full of one color) to win
6. **Advance** to the next level

### Controls

| Input | Action |
|-------|--------|
| Left click | Select / pour between tubes |
| `U` | Undo last move |
| `R` | Reset level |
| `H` | Show hint |
| `ESC` | Back to menu |

## Project Structure (planned)

```
pebbleSort/
├── main.cpp          — Entry point, game loop, rendering, input
├── opencode.json     — opencode project configuration
└── .opencode/        — opencode agents and skills
```

Everything lives in a single `main.cpp` for simplicity. The code is organized into clear sections:

- Data structures (Pebble, Tube, GameState)
- Level generation (reverse-shuffle algorithm)
- Solver (BFS for hints)
- Rendering (Raylib draw calls)
- Input handling (mouse/keyboard)
- Game state machine (Menu → LevelSelect → Playing → Win)
- UI / HUD (buttons, move counter)

## Difficulty Progression

| Levels | Colors | Pebbles per Tube | Shuffle Depth |
|--------|--------|------------------|---------------|
| Early  | 3–4    | 3                | 200           |
| Mid    | 5–7    | 4                | 500           |
| Late   | 8–10   | 5                | 1000+         |

## Acknowledgments

- Inspired by the classic *Water Sort Puzzle* mobile game
- Built with [Raylib](https://www.raylib.com/) — the simple, easy-to-use graphics library
