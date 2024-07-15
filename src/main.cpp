#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <chrono>


#include "Math.hpp"
#include "Rect.hpp"
#include "World.hpp"

#define SFML_WRAPPER_IMPLEMENTATION
#include "sfml_wrapper.hpp"
#define BACKEND_WRAPPER_IMPLEMENTATION
#include "backend_wrapper.hpp"


World world;


void render_physics() {
    while(!BackWrapper::exit_app) {
        std::unique_lock<std::mutex> lock(BackWrapper::mtx_render_callbacks);
            
            BackWrapper::render_callbacks.clear();
            for(Body* body: world.bodies) {
                BackWrapper::render_callbacks.push_back(std::pair<RenderCallback,void*>(BackWrapper::render_rect,body));
                BackWrapper::render_callbacks.push_back(std::pair<RenderCallback,void*>(BackWrapper::render_point,&body->pos));
            }

        lock.unlock();
        BackWrapper::cnd_render_callback.notify_one();
    }
}

void physics() {
    world.addBody(new Rect(Vec2(100,400),Vec2(50,50)));
    world.addBody(new Rect(Vec2(400,500),Vec2(680,50),true));

    while(!BackWrapper::exit_app) {
        std::pair<bool, float> frame_info = world.tick();
        bool ready = frame_info.first; 
        float dt = frame_info.second; 
        if(!ready) continue;

        world.bodies[0]->applyForce(Vec2(0,10));
        if(BackWrapper::key_pressed(BackWrapper::Keys::Left)) {
            world.bodies[0]->applyForce(Vec2(-5,0));
        } 
        if (BackWrapper::key_pressed(BackWrapper::Keys::Right)) {
            world.bodies[0]->applyForce(Vec2(5,0));
        }
        if (BackWrapper::key_pressed(BackWrapper::Keys::Up)) {
            world.bodies[0]->applyForce(Vec2(0,-20));
        }
        if (BackWrapper::key_pressed(BackWrapper::Keys::Down)) {
            world.bodies[0]->applyForce(Vec2(0,5));
        }
        if (BackWrapper::key_pressed(BackWrapper::Keys::R)) { 
            world.bodies[0]->applyTorque(10);
        }
        if (BackWrapper::key_pressed(BackWrapper::Keys::F)) { 
            world.bodies[0]->applyTorque(-10);
        }        

        world.simulate(dt);
    }
}

int main() {
    SfmlWrapper::use();
    BackWrapper::init();
    BackWrapper::run(physics,render_physics);
    return 0;
}
