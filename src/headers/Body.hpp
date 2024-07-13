#ifndef Body_H
#define Body_H

#include <string>
#include "Math.hpp"


class Body {
public:
    std::string uuid;
    Vec2 pos;
    float rotation = 0;
    Vec2 vel;
    float ang_vel = 0;
    
    Vec2 force;
    float torque = 0;
    
    float mass, invMass;
    float inertia, invIneria;
    

    ~Body();
    Body(Vec2 pos , float mass);
    void applyForce(Vec2 f);
    void applyTorque(float t);
};

#endif // Body_H