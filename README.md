# Raylib Tetris

This repository contains a simple Tetris clone written in C++ using the [raylib](https://www.raylib.com) library.

## Project

- **Language:** C++
- **Graphics:** raylib
- **Purpose:** learning to use the library and implementing the classic game Tetris

## Project structure

```
CMakeLists.txt
src/
  Block.cpp/.hpp
  Colors.cpp/.hpp
  Game.cpp/.hpp
  Grid.cpp/.hpp
  Position.cpp/.hpp
  main.cpp
fonts/
sounds/
```

The project uses CMake for cross-platform building and automatically pulls raylib as a dependency.

## Build and run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/IB1aZe/simple-raylib-tetris
   cd simple-raylib-tetris
   ```

2. **Create a build directory and run CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. **Run the game:**
   - On Windows: `\.\Tetris.exe`
   - On Linux/macOS: `./Tetris`

> ⚠️ **Note:** After building, make sure to copy the `fonts` and `sounds` folders from the project root into the same directory as the generated executable. The game expects these resources next to the binary.

If you already have raylib installed, set `CMAKE_PREFIX_PATH` or disable fetching in `CMakeLists.txt`.

## Dependencies

- C++ compiler (e.g., MSVC, gcc, clang)
- CMake 3.11+
- raylib (fetched automatically via FetchContent)

## Gameplay

- **Movement:** left/right arrows to move the piece
- **Rotate:** press the `Space` key to rotate the piece
- **Drop:** down arrow for soft drop

Clear as many lines as possible to increase the score.

## Possible improvements

- Add high score saving
- Support localization


## License

Open project; no license specified.

---
