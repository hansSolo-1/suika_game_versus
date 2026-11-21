#pragma once

#include <core/Vec2.hpp>

struct Fruit
{
    int id = 0;
    Vec2 pos;
    Vec2 prevPos;
    Vec2 accumulatedAccel;
    int tier = 0;
    bool alive = true;
    int age = 0;
};
