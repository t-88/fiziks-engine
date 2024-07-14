#ifndef COLLISION_DETECTOIN_H
#define COLLISION_DETECTOIN_H
#include "Rect.hpp"


namespace CollisionDetection
{
    bool SAT(Rect a, Rect b, Vec2& MTV,float& depth);
    std::pair<int,std::array<Vec2,2>> getContactPoints(Rect a, Rect b);
} 


#endif // COLLISION_DETECTOIN_H
