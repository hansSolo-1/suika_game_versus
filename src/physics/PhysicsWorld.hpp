#pragma once
#include <vector>
#include "core/Vec2.hpp"
#include "physics/Fruit.hpp"

struct MergeEvent {
    int  createdTier = 0;   
    Vec2 pos;              
    int  idA = 0;          
    int  idB = 0;
};

class PhysicsWorld
{
private:
    std::vector<Fruit>      fruits_;
    std::vector<MergeEvent> events_;
    int                     nextId_ = 0;

public:
    int addFruit(int tier, Vec2 pos);
    void step();
    const std::vector<Fruit>& fruits() const;
    const std::vector<MergeEvent>& mergeEvents() const;
    void clearEvents();
    void clear();
};