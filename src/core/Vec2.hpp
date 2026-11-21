#pragma once
#include <cmath>

struct Vec2
{
    float x = 0.0f, y = 0.0f;

    Vec2 operator+(Vec2 v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(Vec2 v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(float n) const { return {x * n, y * n}; }
    Vec2 operator/(float n) const { return {x / n, y / n}; }

    Vec2& operator+=(Vec2 v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2& operator-=(Vec2 v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec2& operator*=(float n) {
        x *= n;
        y *= n;
        return *this;
    }

    float lengthSquared() {return x * x + y * y;}
    float length() {return std::sqrt(lengthSquared());}
};

inline Vec2 operator*(float n, Vec2 v) {return v * n;}

inline float dot(Vec2 a, Vec2 b) {return a.x * b.x + a.y * b.y;}

inline Vec2 normalizeOr(Vec2 v, Vec2 fallback = {0.0f, -1.0f}){
    float len = v.length();
    return len > 1e-6f ? v / len : fallback; //mayor que 0
}
