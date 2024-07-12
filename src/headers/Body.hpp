#ifndef Body_H
#define Body_H

#include <string>
#include "Math.hpp"


class Body {
public:
    Vec2 pos;
    Vec2 vel;
    float mass, invMass;
    Vec2 force;
    std::string uuid;

    ~Body();
    Body(Vec2 pos , float mass);
};

#endif // Body_H