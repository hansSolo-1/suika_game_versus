cmake_minimum_required(VERSION 3.28)
project(SuikaVersus LANGUAGES CXX)

# C++17, no compiler-specific extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put the executable in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- SFML 3.0.1 ---
include(FetchContent)

# Only Graphics (pulls Window and System). Audio/Network off until Phase 8.
set(SFML_BUILD_AUDIO   OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
# Static linking (step 0.4): no DLLs next to the .exe
set(BUILD_SHARED_LIBS  OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.1        # exact tag, never a branch
    GIT_SHALLOW    ON           # download only that commit
    EXCLUDE_FROM_ALL            # don't build/install SFML extras
    SYSTEM                      # silence warnings from SFML headers
)
FetchContent_MakeAvailable(SFML)

# --- Game executable ---
add_executable(suika-versus src/main.cpp)
target_link_libraries(suika-versus PRIVATE SFML::Graphics)