#include <string>
#include "CollisionDetection.hpp"
#include "World.hpp"


World::~World() {}
World::World() {}

void World::addBody(Body* body) {
    bodies.push_back(body);
}


// Sim Loop
void World::simulate(float dt) {
    this->dt = dt;

    checkCollisions();
    applyForces();
    solveConstrains();
    updatePositions();
}

void World::checkCollisions() {
    //TODO: improve O(N^2) broad collision
    for(int i = 0; i < bodies.size(); i++) {
        Body* a = bodies[i];
        for(int j = 0; j < bodies.size(); j++) {
            Body* b = bodies[j];
            if(i == j) continue;    // skip self
            if(a->isStatic && b->isStatic) continue; // if both static do noth

            Arbiter arbiter(a,b);
            if(arbiter.collided) {

                if(a->isStatic) {
                    b->pos += arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap; 
                } else if(b->isStatic) {
                    a->pos -= arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap; 
                } else {
                    a->pos -= arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap / 2.f; 
                    b->pos += arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap / 2.f; 
                }


                arbiter.contact = CollisionDetection::getContactPoints(*static_cast<Rect*>(a),*static_cast<Rect*>(b));
                arbiters.erase(a->uuid + b->uuid);
                arbiters.insert(std::pair<std::string,Arbiter>(a->uuid + b->uuid, arbiter));

                float restitution = 0.5;
                float impulse = -(1 + restitution) * ((b->vel - a->vel) * arbiter.collisionInfo.normal) / (arbiter.collisionInfo.normal * arbiter.collisionInfo.normal * (a->invMass + b->invMass));
                a->vel -= arbiter.collisionInfo.normal * impulse * a->invMass;
                b->vel += arbiter.collisionInfo.normal * impulse * b->invMass;


            } else {
                arbiters.erase(a->uuid + b->uuid);
            }
        }
    }
}
void World::applyForces() {
    for(auto body : bodies) {
        Vec2 acc = body->force * body->invMass;

        float ang_acc = body->torque * body->invIneria;

        body->vel += acc * dt;
        body->ang_vel += ang_acc * dt;
    }
}
void World::solveConstrains() {

}
void World::updatePositions() {
    for(auto body : bodies) {
        body->pos += body->vel * dt;
        body->rotation += body->ang_vel * dt;
        
        body->force = Vec2(0,0);
        body->torque = 0;
    }
}