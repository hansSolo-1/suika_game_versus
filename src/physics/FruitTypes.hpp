#pragma once

#include <cstdint>
#include <array>

struct FruitType
{
    const char* name;
    float radius;
    int points;
    std::uint8_t r, g, b;
};

inline constexpr int numTiers = 11;

inline constexpr std::array<FruitType, numTiers> fruitTypes = {{
    {"Cereza", 13.f, 1, 180,   0,  40},
    {"Frutilla", 17.f, 3, 255,  90, 110},
    {"Uvas", 23.f, 6, 140,  70, 200},
    {"Mandarina", 26.f, 10, 255, 180,  40},
    {"Narnaja", 33.f, 15, 255, 115,  20},
    {"Manzana", 41.f, 21, 230,  30,  30},
    {"Pera", 48.f, 28, 190, 210,  70},
    {"Durazno", 56.f, 36, 255, 185, 185},
    {"piña", 66.f, 45, 245, 205,  40},
    {"Melon", 80.f, 55, 160, 220, 120},
    {"Sandia", 100.f, 66,  30, 130,  40},
}};
