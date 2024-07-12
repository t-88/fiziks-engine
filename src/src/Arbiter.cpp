#include <stdio.h>

#include "Arbiter.hpp"
#include "Rect.hpp"
#include "Math.hpp"

Arbiter::~Arbiter() {}
Arbiter::Arbiter(Body* a, Body* b): a(a), b(b) {
    if(AABB(*static_cast<Rect*>(a),*static_cast<Rect*>(b))) {
        printf("Collision\n");
    }
}


