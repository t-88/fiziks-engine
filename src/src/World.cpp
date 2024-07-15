#include <string>
#include <chrono>
#include <thread>
#include <math.h>

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
    

    this->dt /= (float)iterations;
    for(int i = 0; i < iterations; i++) {
        arbiters.clear();
        checkCollisions();
        solveConstrains();
        applyForces();
        updatePositions();
    }
    for(auto body : bodies) {
        body->force = Vec2(0,0);
        body->torque = 0;
    }    
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
                arbiters.erase(a->uuid + b->uuid);
                arbiters.insert(std::pair<std::string,Arbiter>(a->uuid + b->uuid, arbiter));
            } 
            else {
                arbiters.erase(a->uuid + b->uuid);
            }
        }
    }
}

void World::solveConstrains() {
    for(const auto& elem : arbiters) {
        Vec2 impluses[2];
        auto arbiter = elem.second;
        auto a = arbiter.a; 
        auto b = arbiter.b;

        if(a->isStatic) {
            b->pos += arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap; 
        } else if(b->isStatic) {
            a->pos -= arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap; 
        } else {
            a->pos -= arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap / 2.f; 
            b->pos += arbiter.collisionInfo.normal * arbiter.collisionInfo.overlap / 2.f; 
        }


        arbiter.contact = CollisionDetection::getContactPoints(*static_cast<Rect*>(a),*static_cast<Rect*>(b));

        for(int i = 0; i < arbiter.contact.first; i++) {
            Vec2 contact_point = arbiter.contact.second[i];
            Vec2 r_ap = (contact_point - a->pos).normal(); 
            Vec2 r_bp = (contact_point - b->pos).normal();
            float restitution = 0.5;
            Vec2 rvel = b->vel + (r_bp * b->ang_vel) - a->vel - (r_ap * a->ang_vel);
            
            if(rvel * arbiter.collisionInfo.normal > 0) {
                continue;
            }

            float denom = a->invMass + 
                          b->invMass +  
                          std::pow(r_ap * arbiter.collisionInfo.normal,2) * a->invIneria + 
                          std::pow(r_bp * arbiter.collisionInfo.normal,2) * b->invIneria;
            float nenom = -(1 + restitution) * (rvel * arbiter.collisionInfo.normal);
            float impulse =  nenom / denom;
            impluses[i] = impulse * arbiter.collisionInfo.normal / (float)arbiter.contact.first; 
        }
             
        for(int i = 0; i < arbiter.contact.first; i++) {
            Vec2 contact_point = arbiter.contact.second[i];
            Vec2 r_ap = (contact_point - a->pos); 
            Vec2 r_bp = (contact_point - b->pos); 
            Vec2 impulse = impluses[i];
            a->vel -= impulse * a->invMass * dt;
            b->vel += impulse * b->invMass * dt;
            a->ang_vel -= r_ap.cross(impulse) * a->invIneria * dt;
            b->ang_vel += r_bp.cross(impulse) * b->invIneria * dt;
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

void World::updatePositions() {
    for(auto body : bodies) {
        body->pos += body->vel * dt;
        body->rotation += body->ang_vel * dt;
    }
}