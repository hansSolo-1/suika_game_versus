// PhysicsWorldFake.cpp
// FAKE physics for B and C while the real one is built (USE_FAKE_PHYSICS=ON).
// Rules (week-1 doc, B1): constant fall 5 u/tick, stop on floor or on a fruit
// below with horizontal overlap, no merges. Never compiled together with PhysicsWorld.cpp.
#include "physics/PhysicsWorld.hpp"
#include "physics/FruitTypes.hpp"
#include "core/Config.hpp"
#include <cmath>

namespace {
    // TODO: replace with the names in core/Config.hpp
    constexpr float kFloorY    = boxHeight;  // board height, y grows downward
    constexpr float kFallSpeed = 5.0f;    // 300 u/s at 60 ticks/s

    // TODO: replace with the FruitTypes.hpp lookup (roadmap table 1.2)
    float radiusOf(int tier) {
        static const float r[11] = {fruitTypes[0].radius, fruitTypes[1].radius, fruitTypes[2].radius, fruitTypes[3].radius, fruitTypes[4].radius, fruitTypes[5].radius, fruitTypes[6].radius, fruitTypes[7].radius, fruitTypes[8].radius, fruitTypes[9].radius, fruitTypes[10].radius};
        return (tier >= 0 && tier < 11) ? r[tier] : 13.0f;
    }
}

int PhysicsWorld::addFruit(int tier, Vec2 pos) {
    fruits_.push_back({nextId_, pos, pos, {0.0f, 0.0f}, tier, true, 0});
    return nextId_++;
}

const std::vector<Fruit>& PhysicsWorld::fruits() const { return fruits_; }

const std::vector<MergeEvent>& PhysicsWorld::mergeEvents() const { return events_; }  // always empty

void PhysicsWorld::step() {
    // Container order = id order -> deterministic.
    for (std::size_t i = 0; i < fruits_.size(); ++i) {
        Fruit& f = fruits_[i];
        if (!f.alive) continue;

        const float ri = radiusOf(f.tier);
        float newY = f.pos.y + kFallSpeed;

        // Floor
        if (newY > kFloorY - ri) newY = kFloorY - ri;

        // Fruits below with horizontal overlap: stop exactly touching (circle contact)
        for (std::size_t j = 0; j < fruits_.size(); ++j) {
            if (j == i || !fruits_[j].alive) continue;
            const Fruit& g = fruits_[j];
            if (g.pos.y <= f.pos.y) continue;                 // only fruits below

            const float sumR = ri + radiusOf(g.tier);
            const float dx   = f.pos.x - g.pos.x;
            if (std::fabs(dx) >= sumR) continue;              // no horizontal overlap

            const float limit = g.pos.y - std::sqrt(sumR * sumR - dx * dx);
            if (newY > limit) newY = limit;
        }

        f.prevPos = f.pos;   // keeps "velocity = pos - prevPos" meaningful for the renderer/AI
        f.pos.y   = newY;
        ++f.age;
    }
}

void PhysicsWorld::clearEvents() { events_.clear(); }

void PhysicsWorld::clear() {
    events_.clear();
    fruits_.clear();
    nextId_ = 0;
}