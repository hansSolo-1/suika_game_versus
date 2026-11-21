#pragma once

#include <cstdint>
#include <random>
#include <vector>
#include "core/PlayerInput.hpp"
#include "physics/PhysicsWorld.hpp"

class Board
{
private:
    PhysicsWorld world_;
    std::mt19937 rng_;
    float cursorX_ = 0.f;
    int heldTier_ = 0;
    int nextTier_ = 0;
    int heldId_ = 0;
    int score_ = 0;
    int dropCooldown_ = 0;
    int gameOverTimer_ = 0;
    int settledTicks_ = 0;                       
    bool lost_ = false;

public:
    explicit Board(std::uint32_t seed);

    void update(const PlayerInput& input);
    bool isLost() const { return lost_; }

    const std::vector<Fruit>& fruits() const { return world_.fruits(); }
    float cursorX() const { return cursorX_; }
    int heldTier() const { return heldTier_; }
    int nextTier() const { return nextTier_; }
    int heldFruitId() const { return heldId_; }     
    int score() const { return score_; }
    int gameOverTimer() const { return gameOverTimer_; }

    void forceDrop(float x);
    void stepHeadless();
    const bool isSettled();
    int heldFruitId();
};
