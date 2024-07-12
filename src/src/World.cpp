#include <string>
#include "World.hpp"


World::~World() {}
World::World() {}

void World::addBody(Body* body) {
    bodies.push_back(body);
}


// Sim Loop
void World::collisionsCheck() {
    //TODO: improve O(N^2) broad collision
    
    for(int i = 0; i < bodies.size(); i++) {
        for(int j = 0; j < bodies.size(); j++) {
            if(i == j) continue;    // skip self
            if(bodies[i]->invMass == 0 && bodies[j]->invMass == 0) continue; // if both static do noth

            Arbiter arbiter(bodies[i],bodies[j]);
            if(arbiter.contact.size() > 0) {
                arbiters.insert(std::pair<std::string,Arbiter>(bodies[i]->uuid + bodies[j]->uuid, arbiter));
            } else {
                arbiters.erase(bodies[i]->uuid + bodies[j]->uuid);
            }
        }
    }

}