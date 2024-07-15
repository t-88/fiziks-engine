#include "Rect.hpp"
#include "Math.hpp"
#include <math.h>

Rect::~Rect(){ }
Rect::Rect(Vec2 pos, Vec2 size,float rotation,bool isStatic) : Body(pos,size.x * size.y,rotation,isStatic) ,  size(size)  {     
    inertia = mass *  (size.x * size.x  + size.y * size.y) / 12.f;
    invIneria = 1.f/inertia;

    if(isStatic) {
        mass = 0;
        invMass = 0;
        inertia = 0;
        invIneria = 0;
    }

}

const std::array<Vec2,4>& Rect::getPoints()  {
    points[0] = Vec2(-size.x / 2,-size.y / 2);
    points[1] = Vec2(+size.x / 2,-size.y / 2);
    points[2] = Vec2(+size.x / 2,+size.y / 2);
    points[3] = Vec2(-size.x / 2,+size.y / 2);
    

    for(int i = 0; i < 4; i++) {
        points[i] = Vec2(points[i].x * cos(rotation) - points[i].y * sin(rotation), 
                         points[i].x * sin(rotation) + points[i].y * cos(rotation));
    }

    points[0] += Vec2(pos.x,pos.y);
    points[1] += Vec2(pos.x,pos.y);
    points[2] += Vec2(pos.x,pos.y);
    points[3] += Vec2(pos.x,pos.y);    



    return points;
}



