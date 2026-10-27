# Suika Versus

Two-player split-screen Suika Game (human vs human, human vs CPU).
C++17, SFML 3.0.1, custom Verlet physics.

## Requirements

| Tool | Version | Notes |
|---|---|---|
| C++ compiler | C++17 | Windows: MSVC (Build Tools for Visual Studio 2022, "Desktop development with C++"). Linux: GCC 13+ or Clang 16+ |
| CMake | 3.28+ | `cmake --version` |
| Git | any | Required by CMake to download SFML |

SFML is **not** installed manually. CMake downloads and builds SFML 3.0.1 automatically.

### Windows install (PowerShell)

```powershell
winget install Microsoft.VisualStudio.2022.BuildTools --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
winget install Kitware.CMake
winget install Git.Git
```

### Linux install (Debian/Ubuntu)

```bash
sudo apt install build-essential cmake git \
    libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
    libgl1-mesa-dev libfreetype-dev
```

## Build

### Windows

Run from the repository root:

```powershell
git clone <repo-url> suika-versus
cd suika-versus

cmake -S . -B build                      # configure (first time only)
cmake --build build --config Debug       # Debug build
cmake --build build --config Release     # Release build
```

### Linux

Single-config generator: one build folder per configuration.

```bash
cmake -S . -B build-debug   -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-debug   -j
cmake --build build-release -j
```

## Run

| Platform | Executable |
|---|---|
| Windows | `build\bin\Debug\suika-versus.exe` / `build\bin\Release\suika-versus.exe` |
| Linux | `build-debug/bin/Debug/suika-versus` / `build-release/bin/Release/suika-versus` |

The `assets/` folder is copied next to the executable on every build. The executable folder (executable + `assets/`) can be copied to another PC and run directly: on Windows, SFML and the MSVC runtime are linked statically, so no DLLs are needed.

## Build notes

- **First build:** downloads and compiles SFML. Measured time: `__ min` (fill in). Later builds take seconds.
- **Clean rebuild** (needed after changing cache options in `CMakeLists.txt`):
  ```powershell
  Remove-Item -Recurse -Force build    # Windows
  rm -rf build-debug build-release     # Linux
  ```
- **Font:** loaded from `assets/fonts/font.ttf`; falls back to `C:/Windows/Fonts/arial.ttf`.
- **VS Code:** with the CMake Tools extension, use `CMake: Build` (F7) and `CMake: Debug` (Ctrl+F5). Use the "C++ (Windows)" debugger, not GDB.

## Project structure

```
suika-versus/
|-- CMakeLists.txt
|-- README.md
|-- assets/
|   `-- fonts/font.ttf
`-- src/
    `-- main.cpp
```
