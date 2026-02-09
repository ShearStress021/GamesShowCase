# 🎮 Games Show Case

A collection of small-to-medium games written in **C++**, built for learning, experimentation, and fun.  
This repository uses modern C++ alongside popular game development libraries such as **raylib** and **SDL3**.

Each game lives in its own directory and can be built and run independently.

---

## 🧩 Games Included

| Game | Library | Status | Description |
|-----|--------|--------|-------------|
| `armageddonClash` | raylib | 🧪 Prototype | Short description |
| `game-name-2` | SDL3 | 🚧 In Progress | Short description |
| `game-name-3` | raylib | 🧪 Prototype | Short description |

> This list will grow as more games are added.

---

## 🛠️ Tech Stack

- **Language:** C++ (C++17 / C++20)
- **Libraries:**
  - [raylib](https://www.raylib.com/)
  - [SDL3](https://libsdl.org/)
- **Build Systems:**
  - CMake (recommended)
  - Make (for simple projects)

---

## 🚀 Building & Running

### Prerequisites

Make sure you have:
- A C++ compiler (GCC / Clang / MSVC)
- CMake 3.20+
- raylib and/or SDL3 installed

---

### Build a Specific Game (CMake)

```bash
cd games/game-name
mkdir build
cd build
cmake ..
cmake --build .

