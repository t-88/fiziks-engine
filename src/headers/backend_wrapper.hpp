#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Math.hpp"
#include "World.hpp"


#ifndef BACKEND_WRAPPER_HPP
#define BACKEND_WRAPPER_HPP

typedef void (*RenderCallback)(void* data);
typedef void (*Callback)();

namespace BackWrapper {
    namespace Keys {
        enum InputKey {
            Left = 0,
            Right,
            Up,
            Down,
            R,
            F,
        };
    } 

    const int FPS = 60; 
    extern std::map<int,int> input;
    extern bool exit_app;
    extern std::mutex mtx_render_callbacks;
    extern std::condition_variable cnd_render_callback;
    extern std::list<std::pair<RenderCallback,void*>> render_callbacks;
    extern Vec2 mouse_pos;


    // callbacks
    extern  void (*init)();
    extern  void (*render)();
    extern  bool (*key_pressed)(int);
    extern  bool (*mouse_down)(int);
    extern  RenderCallback render_rect;
    extern  RenderCallback render_point;


    // gets called inside the renderer backend, renders
    void render_the_render_list();
    void run(Callback physics_sim,Callback render_physics);

} 


    


#endif //BACKEND_WRAPPER_HPP

#ifdef BACKEND_WRAPPER_IMPLEMENTATION

namespace BackWrapper {
    std::map<int,int> input;
    bool exit_app = false;
    std::mutex mtx_render_callbacks;
    std::condition_variable cnd_render_callback;
    std::list<std::pair<RenderCallback,void*>> render_callbacks;
    Vec2 mouse_pos;

    void (*init)();
    void (*render)();
    bool (*key_pressed)(int);
    bool (*mouse_down)(int);
    RenderCallback render_rect;
    RenderCallback render_point;

    void render_the_render_list() {
        std::unique_lock<std::mutex> lock(mtx_render_callbacks);
        cnd_render_callback.wait(lock);
        for(std::pair<RenderCallback,void*> callback  : render_callbacks) {
            callback.first(callback.second);
        }
        lock.unlock();
    }


    void run(Callback physics_sim,Callback render_physics)  {
        std::thread physics_thread(physics_sim);
        std::thread physics_renderer_thread(render_physics);
        std::thread renderer_thread(render);

        physics_thread.join();
        physics_renderer_thread.join();
        renderer_thread.join();
    }
}


#endif //BACKEND_WRAPPER_IMPLEMENTATION