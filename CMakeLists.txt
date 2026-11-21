cmake_minimum_required(VERSION 3.28)
project(SuikaVersus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FIX 5: single-config generators (Ninja/Makefiles) need a build type, or $<CONFIG> is empty
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Same output path for every generator: build/bin/Debug or build/bin/Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# --- Step 0.4: fully static build ---
# Static MSVC runtime (/MT, /MTd). Must be set BEFORE FetchContent.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

set(SFML_BUILD_AUDIO         OFF CACHE BOOL "" FORCE)  # turn ON when sound is added (1-8 Dec)
set(SFML_BUILD_NETWORK       OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS        OFF CACHE BOOL "" FORCE)  # SFML as static libs
set(SFML_USE_STATIC_STD_LIBS ON  CACHE BOOL "" FORCE)  # SFML uses /MT too

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.1
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

option(USE_FAKE_PHYSICS "Compile PhysicsWorldFake.cpp instead of PhysicsWorld.cpp" ON)

# FIX 1: only files that exist. Add SpatialGrid.cpp when it is created.
set(PHYSICS_REAL
    src/physics/PhysicsWorld.cpp
    # src/physics/SpatialGrid.cpp
)
set(PHYSICS_FAKE
    src/physics/PhysicsWorldFake.cpp
)
# FIX 6: uncomment each line when its .cpp exists (a missing file breaks configure)
set(GAME_SRC
    # src/game/Board.cpp
    # src/game/Game.cpp
    # src/input/KeyboardController.cpp
    # src/render/BoardRenderer.cpp
    # src/ai/RandomAIController.cpp
    # src/ai/Evaluator.cpp
)

function(common_setup target)
    target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

# ---- 1. the game ----  (FIX 2: name)
add_executable(suika src/main.cpp ${GAME_SRC})
if(USE_FAKE_PHYSICS)
    target_sources(suika PRIVATE ${PHYSICS_FAKE})
    message(STATUS "Physics: FAKE")
else()
    target_sources(suika PRIVATE ${PHYSICS_REAL})
    message(STATUS "Physics: REAL")
endif()
common_setup(suika)
target_link_libraries(suika PRIVATE SFML::Graphics)

# ---- 2. physics sandbox: always real physics ----
add_executable(physics_sandbox tests/physics_sandbox.cpp ${PHYSICS_REAL})
common_setup(physics_sandbox)
target_link_libraries(physics_sandbox PRIVATE SFML::Graphics)

# ---- 3. evaluator tests: no window, no physics ----  (FIX 2: names/paths)
add_executable(evaluator_tests tests/evaluator_tests.cpp src/ai/Evaluator.cpp)
common_setup(evaluator_tests)

# ---- Step 0.5: copy assets/ next to the game ----  (FIX 3: one copy only)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:suika>/assets
    COMMENT "Copying assets"
)
add_dependencies(suika copy_assets)   # FIX 4: runs even when CLion builds only suika

# ---- ctest ----
enable_testing()
add_test(NAME physics_determinism COMMAND physics_sandbox --headless)
add_test(NAME evaluator           COMMAND evaluator_tests)