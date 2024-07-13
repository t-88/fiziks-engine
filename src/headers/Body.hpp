#ifndef Body_H
#define Body_H

#include <string>
#include "Math.hpp"


class Body {
public:
    std::string uuid;
    Vec2 pos;
    Vec2 vel;
    Vec2 force;
    float mass, invMass;
    

    ~Body();
    Body(Vec2 pos , float mass);
    void applyForce(Vec2 force);
};

#endif // Body_H