#pragma once

#include "core/PlayerInput.hpp"

class Board;

class Controller
{
public:
    virtual ~Controller() = default;
    virtual PlayerInput update(const Board& board) = 0;

    virtual void reset();
};