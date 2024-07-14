#include <stdio.h>

#include "Arbiter.hpp"
#include "Rect.hpp"
#include "Math.hpp"
#include "CollisionDetection.hpp"

Arbiter::~Arbiter() {}
Arbiter::Arbiter(Body* a, Body* b): a(a), b(b) {
    if(CollisionDetection::SAT(*static_cast<Rect*>(a),*static_cast<Rect*>(b),collisionInfo.normal,collisionInfo.overlap)) {
        collided = true;
    }
}


