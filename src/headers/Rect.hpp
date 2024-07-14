#ifndef RECT_H
#define RECT_H

#include "Body.hpp"
#include <array>

class Rect : public Body {
public:
    std::array<Vec2,4> points;
    Vec2 size;


    ~Rect();
    Rect(Vec2 pos, Vec2 size,bool isStatic = false);
    const std::array<Vec2,4>& getPoints(); 
};




#endif // RECT_H