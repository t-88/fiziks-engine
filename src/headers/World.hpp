#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>

#include "Body.hpp"
#include "Arbiter.hpp"



class World {
public:
    std::vector<Body*> bodies;
    std::map<std::string,Arbiter> arbiters;
    float dt;

    ~World();
    World();

    // Functions
    void addBody(Body* body);


    // Sim Loop
    void simulate(float dt);
    void checkCollisions();
    void applyForces();
    void solveConstrains();
    void updatePositions();


    
};

#endif // WORLD_H
