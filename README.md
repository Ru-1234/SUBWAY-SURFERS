# Subway Surfers 
**Students:** i240053 · i240061 · i240054    
**Language:** C++  
**Graphics & Audio Library:** SFML 2.5  
**Build System:** CMake (or direct Makefile)

---

## Table of Contents

1. [Game Overview](#game-overview)
2. [Project Structure](#project-structure)
3. [OOP Concepts Used](#oop-concepts-used)
4. [Dependencies](#dependencies)
5. [How to Build & Run](#how-to-build--run)
6. [Fix Required Before Running](#fix-required-before-running)
7. [Menu Navigation](#menu-navigation)
8. [Game Controls](#game-controls)
9. [Gameplay Mechanics](#gameplay-mechanics)
10. [Obstacles](#obstacles)
11. [Power-Ups](#power-ups)
12. [Scoring System](#scoring-system)
13. [Class Descriptions](#class-descriptions)
14. [File Descriptions](#file-descriptions)
15. [Common Errors & Fixes](#common-errors--fixes)

---

## Game Overview

This is a **Subway Surfers-inspired endless runner** built with C++ and SFML. The player runs across 3 lanes, dodges incoming obstacles (trains, barriers, cones, fences, policemen), collects coins, and picks up power-ups to survive as long as possible. The game gets faster every 10 seconds. Your score is saved to a leaderboard.

---

## Project Structure

```
OOP-project/
├── main.cpp                        ← Entry point (calls GameEngine)
├── CMakeLists.txt                  ← CMake build script
├── arial.ttf                       ← Font file
├── assets/
│   ├── subway_music.ogg            ← Background music (used by game)
│   ├── subway_music.wav            ← Alternate audio format
│   └── subway_music_fixed.wav      ← Fixed audio version
├── Images/
│   ├── bg.png                      ← Menu/game background
│   ├── bgg.png                     ← Start screen background
│   ├── player.png                  ← Player sprite
│   ├── train.png                   ← Train obstacle sprite
│   ├── barrier.png                 ← Barrier obstacle sprite
│   ├── cone.png                    ← Cone obstacle sprite
│   ├── fence.png                   ← Fence obstacle sprite
│   ├── policeman.png               ← Policeman obstacle sprite
│   ├── coin.png                    ← Coin sprite
│   ├── magnet.png                  ← Magnet power-up sprite
│   ├── jetpack.png                 ← Jetpack power-up sprite
│   ├── shield.png                  ← Shield power-up sprite
│   ├── doublecoin.png              ← Double Coin power-up sprite
│   └── gameover.png                ← Game over screen image
├── PROJECT/
│   ├── GameList.h                  ← Generic dynamic list (template)
│   ├── GameEngine.h / .cpp         ← Main game loop & state manager
│   ├── Player.h / .cpp             ← Player class
│   ├── Obstacle.h / .cpp           ← Obstacle base + child classes
│   ├── PowerUp.h / .cpp            ← PowerUp base + child classes
│   ├── Coin.h / .cpp               ← Coin class
│   ├── ScoreManager.h / .cpp       ← Score & high score management
│   ├── TrackManager.h / .cpp       ← Track, spawning, speed control
│   └── Makefile                    ← Alternative direct make build
└── build/
    ├── SFMLRunner                  ← Pre-compiled Linux executable
    └── highscore.txt               ← Saved high score (auto-updated)
```

---

## OOP Concepts Used

| Concept | Where Used |
|---------|-----------|
| **Classes & Objects** | Player, GameEngine, Coin, ScoreManager, TrackManager |
| **Inheritance** | Train, Barrier, Cone, Fence, Policeman → all inherit from `Obstacle`; MagnetPower, JetpackPower, ShieldPower, DoubleCoinPower → all inherit from `PowerUp` |
| **Polymorphism** | `canJumpOver()`, `canSlideUnder()`, `applyEffect()` are virtual and overridden in each child class |
| **Encapsulation** | All class members are private/protected; accessed through public getters/setters |
| **Templates** | `GameList<T>` is a generic dynamic array used for obstacles, coins, and power-ups |
| **Dynamic Memory** | GameList uses `new`/`delete` and auto-resizes (doubles capacity) |
| **Enums** | `GameState` (START_SCREEN, MENU, NAME_INPUT, PLAYING, LEADERBOARD, INSTRUCTIONS, GAME_OVER) and `PlayerState` (RUNNING, JUMPING, SLIDING) |
| **File I/O** | ScoreManager reads/writes high score from `highscore.txt` |

---

## Dependencies

### SFML 2.5 (Required)

**Ubuntu/Debian Linux:**
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install SFML-devel
```

**Windows:** Download MinGW version from https://www.sfml-dev.org/download.php

**macOS:**
```bash
brew install sfml
```

### CMake (Required for CMake build)
```bash
sudo apt-get install cmake
```

### g++ Compiler
```bash
sudo apt-get install g++
```

---

## Fix Required Before Running

> ⚠️ **CRITICAL:** The code has **hardcoded absolute paths** pointing to the original developer's computer (`/home/maham/Downloads/OOP-project/...`). These will cause crashes on any other machine. You must fix them before building.

### Files to Fix

**1. `PROJECT/GameEngine.cpp`** — find and replace these 3 lines:

```cpp
// ORIGINAL (broken on your PC):
font.loadFromFile("/home/maham/Downloads/OOP-project/arial.ttf")
startBgTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/bgg.png")
menuBgTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/bg.png")
backgroundMusic.openFromFile("/home/maham/Downloads/OOP-project/assets/subway_music.ogg")

// FIXED (use relative paths):
font.loadFromFile("arial.ttf")
startBgTexture.loadFromFile("Images/bgg.png")
menuBgTexture.loadFromFile("Images/bg.png")
backgroundMusic.openFromFile("assets/subway_music.ogg")
```

**2. `PROJECT/Player.cpp`** — find and replace:

```cpp
// ORIGINAL (broken):
playerTexture.loadFromFile("/home/maham/Downloads/OOP-project/Images/player.png")

// FIXED:
playerTexture.loadFromFile("Images/player.png")
```

**3. `PROJECT/Obstacle.cpp`** — similarly fix any hardcoded image paths for train.png, barrier.png, cone.png, fence.png, policeman.png to use `Images/` prefix.

**4. `PROJECT/PowerUp.cpp`** and **`PROJECT/Coin.cpp`** — fix any hardcoded paths for magnet.png, jetpack.png, shield.png, doublecoin.png, coin.png.

After fixing paths, the game must always be **run from the `OOP-project/` folder** so that `Images/`, `assets/`, and `arial.ttf` are found correctly.

---

## How to Build & Run

### Method 1 — Using CMake (Recommended)

```bash
# Step 1: Go to project root
cd OOP-project

# Step 2: Create build directory
mkdir build && cd build

# Step 3: Configure
cmake ..

# Step 4: Compile
make

# Step 5: Run (go back to OOP-project/ first so paths work)
cd ..
./build/SFMLRunner
```

### Method 2 — Using the Direct Makefile

```bash
# Go into the PROJECT folder
cd OOP-project/PROJECT

# Compile
make

# Run (go back to OOP-project/ first)
cd ..
./PROJECT/PROJECT
```

### Method 3 — Pre-built Binary (Linux Only)

If you are on Linux and don't want to recompile:
```bash
cd OOP-project
chmod +x build/SFMLRunner
./build/SFMLRunner
```
> Note: Still requires SFML installed on your system, and paths must be fixed first.

### Building on Windows (Code::Blocks)

1. Install **Code::Blocks with MinGW** from http://www.codeblocks.org/
2. Download **SFML 2.5 for MinGW** from https://www.sfml-dev.org/
3. Create a new C++ project and add all `.cpp` files from `PROJECT/` plus `main.cpp`
4. In Project → Build Options → Linker Settings, add:
   - `sfml-graphics`, `sfml-window`, `sfml-system`, `sfml-audio`
5. Add SFML include and lib paths in Search Directories
6. Fix the hardcoded paths (see above)
7. Build and run — make sure `Images/`, `assets/`, `arial.ttf` are in the same folder as the `.exe`

---

## Menu Navigation

### Start Screen
```
(Background splash image)
PRESS ENTER TO START
Press ESC to Exit
```
| Key | Action |
|-----|--------|
| `Enter` | Go to Main Menu |
| `Esc` | Exit game |

---

### Main Menu
```
SUBWAY SURFERS
1- Start Game
2- Continue
3- LeaderBoard
4- Instructions
5- Exit
```
| Key | Action |
|-----|--------|
| `1` | Start new game (asks for name) |
| `2` | Continue (asks for name if not set; else resumes) |
| `3` | View Leaderboard |
| `4` | View Instructions |
| `5` | Exit game |

---

### Name Input Screen
- Type your name (up to 20 characters)
- A blinking cursor shows your current input
- If you press Enter with no name, it defaults to **"Player"**

| Key | Action |
|-----|--------|
| Any letter/number | Type your name |
| `Backspace` | Delete last character |
| `Enter` | Confirm name and start |
| `Esc` | Go back to menu |

---

### Leaderboard Screen
Shows:
- Current player name
- Current score
- All-time high score + who set it

| Key | Action |
|-----|--------|
| `Space` or `Esc` | Return to menu |

---

### Instructions Screen
```
A/D - Left/Right
W/S - Jump/Slide
```
| Key | Action |
|-----|--------|
| `Space` or `Esc` | Return to menu |

---

### Game Over Screen
Shows:
- GAME OVER
- Player name
- Final score
- High score + holder name

| Key | Action |
|-----|--------|
| `Space` or `Esc` | Return to menu |

---

## Game Controls

| Key | Action |
|-----|--------|
| `A` | Move player to the **left lane** |
| `D` | Move player to the **right lane** |
| `W` | **Jump** over obstacles |
| `S` | **Slide** under obstacles |
| `Esc` | Pause / return to menu |

**3 Lanes:** Left (lane 0) · Center (lane 1, default) · Right (lane 2)

---

## Gameplay Mechanics

### Lane System
The screen is divided into **3 vertical lanes**. The player starts in the center lane. Switching lanes is instant (no sliding animation between lanes).

### Speed Progression
- Game starts at a base speed
- Every **10 seconds**, track speed increases by **+20 units**
- This makes obstacles spawn faster and move down the screen quicker

### Survival Score
- Every **1 second** survived = **+10 points** automatically added

### Collision Detection
- Each obstacle is checked per-frame against the player's bounding box
- Collision is only checked when the player and obstacle are in **the same lane**
- Depending on the obstacle type, jumping or sliding may avoid it (see Obstacles below)

### Background Scrolling
The background scrolls downward to create the illusion of forward movement. Scroll speed is tied to the current track speed.

---

## Obstacles

All obstacles inherit from the base `Obstacle` class and scroll downward at the current track speed.

| Obstacle | Image | Can Jump Over | Can Slide Under | Notes |
|----------|-------|:-------------:|:---------------:|-------|
| **Train** | train.png | ❌ No | ✅ Yes | Deadly if you run into it; must slide under |
| **Barrier** | barrier.png | ✅ Yes | ❌ No | Jump over it |
| **Cone** | cone.png | ✅ Yes | ❌ No | Jump over it |
| **Fence** | fence.png | ❌ No | ✅ Yes | Slide under it |
| **Policeman** | policeman.png | ✅ Yes | ❌ No | Jump over it |

**If you have a Shield active** — hitting an obstacle destroys the obstacle instead of ending the game (one hit protection).

---

## Power-Ups

Power-ups spawn randomly on the track and move downward. Collect by running into them. Each grants **+100 bonus points** on pickup.

| Power-Up | Duration | Effect |
|----------|----------|--------|
| **Magnet** 🧲 | 8 seconds | Automatically collects nearby coins within 100px range (no need to be in same lane) |
| **Jetpack** 🚀 | 6 seconds | Reduces gravity by 50% while jumping — makes jumps float higher and longer |
| **Shield** 🛡️ | 10 seconds | Absorbs one obstacle hit — obstacle is destroyed instead of game over |
| **Double Coin** 💰 | 10 seconds | All coins collected give **2× points** (100 instead of 50) |

**Visual Indicators:** Each active power-up shows a colored circle around the player:
- Shield → Blue circle
- Magnet → Red circle
- Jetpack → Orange circle
- Double Coin → Yellow circle

---

## Scoring System

| Event | Points |
|-------|--------|
| Surviving 1 second | +10 |
| Collecting a coin (normal) | +50 |
| Collecting a coin (Double Coin active) | +100 |
| Collecting a power-up | +100 |
| Magnet auto-collecting a coin | +50 (or +100 with Double Coin) |

**High Score** is saved to `build/highscore.txt` and persists between sessions. The file stores the score and the player name who set it.

---

## Class Descriptions

### `GameEngine`
The central controller. Owns all other objects. Manages:
- The SFML render window (800×600)
- Game state machine (`START_SCREEN → MENU → NAME_INPUT → PLAYING → GAME_OVER` etc.)
- The main game loop: `handleInput()` → `update()` → `render()`
- Background music (loops `subway_music.ogg`)
- All render functions per state

### `Player`
Manages player position, movement, state, and power-up effects.
- 3 lanes at fixed X positions (140, 410, 680)
- States: `RUNNING`, `JUMPING`, `SLIDING`
- Gravity = 1200 units/s² (halved with Jetpack)
- Jump velocity = -600 units/s
- Sliding squishes the player sprite vertically (scale 0.35 → 0.2)

### `Obstacle` (Base Class)
Abstract base for all obstacles. Has lane, position, speed, and sprite.  
Child classes: `Train`, `Barrier`, `Cone`, `Fence`, `Policeman`  
Each overrides `canJumpOver()` and `canSlideUnder()`.

### `PowerUp` (Base Class)
Abstract base for all power-ups. Has pure virtual `applyEffect(Player*)`.  
Child classes: `MagnetPower`, `JetpackPower`, `ShieldPower`, `DoubleCoinPower`

### `Coin`
A simple collectible that scrolls downward. Has rotation animation.  
Worth 50 points normally, 100 with Double Coin active.

### `TrackManager`
Manages all spawning and updating of obstacles, coins, and power-ups using `GameList<T>`.  
Controls current speed and calls `increaseSpeed()` every 10 seconds.  
Also handles background rendering with scroll offset.

### `ScoreManager`
Tracks current score and all-time high score.  
Reads/writes `highscore.txt`. Stores player names (up to 50 chars).

### `GameList<T>` (Template)
A custom dynamic array (like a simplified vector).  
Starts with capacity 10, doubles when full.  
Used for `GameList<Obstacle>`, `GameList<Coin>`, `GameList<PowerUp>`.

---

## File Descriptions

| File | Purpose |
|------|---------|
| `main.cpp` | Entry point — creates GameEngine and calls `run()` |
| `CMakeLists.txt` | CMake build script — links SFML, sets C++17, includes PROJECT/ headers |
| `PROJECT/Makefile` | Alternative build — compiles with `g++ -std=c++11` and links SFML |
| `PROJECT/GameList.h` | Template dynamic array (no .cpp needed — fully in header) |
| `PROJECT/GameEngine.h/.cpp` | Main game controller, state machine, rendering |
| `PROJECT/Player.h/.cpp` | Player movement, jump/slide, power-up state |
| `PROJECT/Obstacle.h/.cpp` | Obstacle hierarchy (Train, Barrier, Cone, Fence, Policeman) |
| `PROJECT/PowerUp.h/.cpp` | PowerUp hierarchy (Magnet, Jetpack, Shield, DoubleCoin) |
| `PROJECT/Coin.h/.cpp` | Collectible coins |
| `PROJECT/ScoreManager.h/.cpp` | Score tracking and file-based persistence |
| `PROJECT/TrackManager.h/.cpp` | Spawning, speed control, background scrolling |
| `arial.ttf` | Font for all in-game text |
| `assets/subway_music.ogg` | Background music (looping) |
| `Images/*.png` | All game sprites |
| `build/highscore.txt` | Saved high score (auto-created/updated) |

---

## Common Errors & Fixes

| Error | Cause | Fix |
|-------|-------|-----|
| Game crashes on startup | Hardcoded `/home/maham/` paths | Fix all paths to relative (see Fix section above) |
| `ERROR: Could not load bgg.png` | Wrong working directory | Run the game from `OOP-project/` folder, not from inside `build/` |
| `SFML/Graphics.hpp: No such file` | SFML not installed | `sudo apt-get install libsfml-dev` |
| `cmake: command not found` | CMake missing | `sudo apt-get install cmake` |
| `make: command not found` | Build tools missing | `sudo apt-get install build-essential` |
| Font shows blank / no text | `arial.ttf` not found | Copy `arial.ttf` to the working directory you run from |
| Music doesn't play | `.ogg` file path wrong | Ensure `assets/subway_music.ogg` exists relative to run location |
| `SFMLRunner` won't run on Windows | Compiled for Linux | Recompile using Code::Blocks + MinGW + SFML for Windows |
| Score not saving | `highscore.txt` write permission | Ensure `build/` folder is writable; or run with proper permissions |

---

## Quick Start (Linux)

```bash
# 1. Extract
unzip subway_surfer.zip && cd OOP-project

# 2. Install SFML
sudo apt-get install libsfml-dev cmake g++

# 3. Fix hardcoded paths in:
#    PROJECT/GameEngine.cpp  (4 paths)
#    PROJECT/Player.cpp      (1 path)
#    PROJECT/Obstacle.cpp    (image paths)
#    PROJECT/PowerUp.cpp     (image paths)
#    PROJECT/Coin.cpp        (image path)
# Change /home/maham/Downloads/OOP-project/ → (nothing, just relative path)

# 4. Build
mkdir -p build && cd build
cmake ..
make
cd ..

# 5. Run from OOP-project/ folder
./build/SFMLRunner
```

---

*README generated from full source code analysis of all .h, .cpp, CMakeLists.txt, and Makefile files.*
