#ifndef ARBITER_H
#define ARBITER_H

#include <vector>
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

class Arbiter {
public:
    Body* a;
    Body* b;
    std::vector<Vec2> contact;

    ~Arbiter();
    Arbiter(Body* a, Body* b);
};



#endif //ARBITER_H