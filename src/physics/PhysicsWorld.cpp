#include "physics/PhysicsWorld.hpp" 

int PhysicsWorld::addFruit(int tier, Vec2 pos){
    fruits_.push_back({nextId_, pos, pos, {0.0f, 0.0f}, tier, true, 0});
    return nextId_++;
}

const std::vector<Fruit>& PhysicsWorld::fruits() const {
    return fruits_;
}

const std::vector<MergeEvent>& PhysicsWorld::mergeEvents() const {
    return events_;
}

void PhysicsWorld::step(){}

void PhysicsWorld::clearEvents(){
    events_.clear();
}

void PhysicsWorld::clear(){
    events_.clear();
    fruits_.clear();
    nextId_ = 0;
}

