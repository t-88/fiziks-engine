#ifndef RECT_H
#define RECT_H

#include "Body.hpp"

class Rect : public Body {
public:
    Vec2 size;

    ~Rect();
    Rect(Vec2 pos, Vec2 size);
};


bool AABB(Rect a, Rect b);



#endif // RECT_H