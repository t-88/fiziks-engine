#ifndef ARBITER_H
#define ARBITER_H

#include <array>
#include "Body.hpp"

struct ArbiterKey {
    Body* a;
    Body* b;
    ArbiterKey(Body* a, Body* b): a(a), b(b) {}
    bool operator==(ArbiterKey other) {
        return a == other.a && b == other.b;
    }
    bool operator<(ArbiterKey other) {
        return a < other.a && b < other.b;
    }
};

struct CollisionInfo {
    float overlap;
    Vec2 normal;
};

class Arbiter {
public:
    Body* a;
    Body* b;
    std::pair<int,std::array<Vec2,2>> contact;
    CollisionInfo collisionInfo;
    Vec2 MTV;
    float depth;
    bool collided = false;

    ~Arbiter();
    Arbiter(Body* a, Body* b);
};



#endif //ARBITER_H