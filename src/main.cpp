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



World world;



void physics() {
    static bool left_pressed = false;

    for(Body* body : world.bodies) {
        body->applyForce(Vec2(0,10));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        world.bodies[0]->applyForce(Vec2(-5,0));
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        world.bodies[0]->applyForce(Vec2(5,0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        world.bodies[0]->applyForce(Vec2(0,-20));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        world.bodies[0]->applyForce(Vec2(0,5));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { 
        world.bodies[0]->applyTorque(10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { 
        world.bodies[0]->applyTorque(-10);
    }        
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!left_pressed) {
            world.addBody(new Rect(Vec2(sf::Mouse::getPosition(SfmlWrapper::window).x,sf::Mouse::getPosition(SfmlWrapper::window).y),
                                   Vec2(rand() % 100 + 20,rand() % 100 + 20),
                                   (rand() % 314) / 100.f)
                        );
            left_pressed = true;
        }
    } else {
        left_pressed = false;
    }
    world.simulate(SfmlWrapper::dt);
}

int main() {
    SfmlWrapper::window.create(sf::VideoMode(800,600),"Fiziks",sf::Style::Titlebar);
    SfmlWrapper::window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width - SfmlWrapper::window.getSize().x, sf::VideoMode::getDesktopMode().height - SfmlWrapper::window.getSize().y) / 2);
    SfmlWrapper::window.setFramerateLimit(FPS);


    world.addBody(new Rect(Vec2(100,400),Vec2(50,50)));
    world.addBody(new Rect(Vec2(400,500),Vec2(800,50),0,true));
    world.addBody(new Rect(Vec2(0,300),Vec2(20,400),0,true));
    world.addBody(new Rect(Vec2(800,300),Vec2(20,400),0,true));
    world.addBody(new Rect(Vec2(100,300),Vec2(200,5),0.2,true));

  

    while(SfmlWrapper::window.isOpen()) {
        while(SfmlWrapper::window.pollEvent(SfmlWrapper::event)) {
            if((SfmlWrapper::event.type == sf::Event::Closed) || 
               (SfmlWrapper::event.type == sf::Event::KeyPressed && SfmlWrapper::event.key.code == sf::Keyboard::Escape)) {
                SfmlWrapper::window.close();
            }
        }

        SfmlWrapper::dt  = SfmlWrapper::clock.restart().asSeconds() * FPS;
        physics();

        SfmlWrapper::window.clear(sf::Color(0x181818FF));
        for(Body* body: world.bodies) {
            Rect* rect = static_cast<Rect*>(body);
            SfmlWrapper::render_rect(*rect);
            SfmlWrapper::render_point(rect->pos);
        }
        
        SfmlWrapper::window.display();
    }


    return 0;
}
