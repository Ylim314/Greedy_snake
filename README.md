# Greedy Snake

A terminal-based Snake game written in C with PDCurses. This project was built as a data structures course project and kept public as a small, complete systems-style program that demonstrates game loop design, state management, and array-based movement logic.

## Demo

- Gameplay video: [videos/screen_record.mp4](videos/screen_record.mp4)

## Highlights

- Built in C with a lightweight terminal UI
- Menu system, pause flow, about page, and mode selection
- Three speed modes: slow, medium, fast
- Score tracking and elapsed time display
- Wrap-around wall behavior
- Random food generation that avoids the snake body
- Cross-platform build path: bundled PDCurses for Windows, curses via CMake on Unix-like systems

## Data Structure And Logic

This repository is worth showing publicly because the implementation is small but explicit:

- The snake body is stored in a fixed-size array of `Point` nodes
- Movement is handled by shifting body segments forward each frame
- Direction updates prevent immediate reversal into the snake body
- Food generation retries until it lands outside occupied cells
- Game state is modeled with an enum-based state machine: menu, playing, paused, game over, about, and mode selection

## Tech Stack

- C99
- PDCurses
- CMake

## Build

### Windows

This repository vendors `PDCurses`, so the simplest path is to use CMake:

```bash
cmake -S . -B build
cmake --build build --config Release
```

### Unix-like Systems

Install a curses implementation first, then build with CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/GreedySnake
```

On Windows with a multi-config generator, the executable may be under `build/Release/GreedySnake.exe`.

## Controls

- Arrow keys: move
- `P`: pause / resume
- `ESC` or `Q`: return to menu
- `Enter`: confirm menu selection

## Project Structure

- `src/main.c`: entry point and main loop
- `src/game.c`: game state updates, scoring, speed, wall handling
- `src/snake.c`: snake movement and self-collision logic
- `src/food.c`: food placement
- `src/input.c`: keyboard handling and menu interaction
- `src/ui.c`: terminal rendering

## Why This Repo Is Public

This is not just a classroom archive. It is a compact C project that shows:

- basic data structure implementation
- terminal UI programming
- state machine design
- clean separation between input, game logic, and rendering

## License

MIT