#include "Rect.hpp"
#include "Math.hpp"

Rect::~Rect(){ }
Rect::Rect(Vec2 pos, Vec2 size) : Body(pos,size.x * size.y) ,  size(size)  { }


bool AABB(Rect a, Rect b) {
    return a.pos.x + a.size.x > b.pos.x &&  a.pos.y + a.size.y > b.pos.y && b.pos.x + b.size.x > a.pos.x && b.pos.y + b.size.y > a.pos.y; 
}
