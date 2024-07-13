#include "Rect.hpp"
#include "Math.hpp"
#include <math.h>

Rect::~Rect(){ }
Rect::Rect(Vec2 pos, Vec2 size) : Body(pos,size.x * size.y) ,  size(size)  { 
    inertia = mass *  pow(size.x,2)  * pow(size.y,2) / 12;
    invIneria = 1.f/inertia;
}


bool AABB(Rect a, Rect b) {
    return a.pos.x + a.size.x > b.pos.x &&  a.pos.y + a.size.y > b.pos.y && b.pos.x + b.size.x > a.pos.x && b.pos.y + b.size.y > a.pos.y; 
}
