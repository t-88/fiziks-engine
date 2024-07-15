#ifndef SFML_WRAPPER_HPP
#define SFML_WRAPPER_HPP


#include <SFML/Graphics.hpp>

#include "backend_wrapper.hpp"
#include "Math.hpp"
#include "Rect.hpp"


namespace SfmlWrapper {
    extern sf::RenderWindow window;
    extern sf::Clock clock;
    extern sf::Event event;
    extern std::map<sf::Keyboard::Key,bool> keys;

    void init();
    bool key_pressed(int k);
    void render_rect(void* data);
    void render_point(void* data);
    void render();
    void use();
}



#endif //SFML_WRAPPER_HPP

#ifdef SFML_WRAPPER_IMPLEMENTATION

namespace SfmlWrapper {
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Event event;
    std::map<sf::Keyboard::Key,bool> keys;


    void init() {
        BackWrapper::input[BackWrapper::Keys::Left] = sf::Keyboard::Left;
        BackWrapper::input[BackWrapper::Keys::Right] = sf::Keyboard::Right;
        BackWrapper::input[BackWrapper::Keys::Up] = sf::Keyboard::Up;
        BackWrapper::input[BackWrapper::Keys::Down] = sf::Keyboard::Down;
        BackWrapper::input[BackWrapper::Keys::R] = sf::Keyboard::R;
        BackWrapper::input[BackWrapper::Keys::F] = sf::Keyboard::F;        
    }

    bool key_pressed(int k) {
        sf::Keyboard::Key key = (sf::Keyboard::Key)(BackWrapper::input[k]);
        if(keys.find(key) == keys.end()) return false;
        return keys.at(key);
    }

   

    void render_rect(void* data) {
        Rect r = *((Rect*)data); 
        Vec2 size = r.size;
        Vec2 pos = r.pos;
        float rotation = r.rotation;
    
        sf::RectangleShape rect(sf::Vector2f(size.x - 2 ,size.y - 2));
        rect.setPosition(sf::Vector2f(pos.x,pos.y));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setOrigin((size.x - 2) / 2, (size.y - 2) / 2 );
        rect.setFillColor(sf::Color::Transparent);
        rect.setRotation(rotation / 3.14f * 180.f );
        
        window.draw(rect);
    }
    void render_point(void* data) { 
        Vec2 pos = *((Vec2*)data);
        
        sf::CircleShape circle(2);
        circle.setPosition(sf::Vector2f(pos.x - 1,pos.y - 1));
        circle.setFillColor(sf::Color(0xFFA500FF));
        
        window.draw(circle);
    }    
    void render() {
        window.create(sf::VideoMode(800,600),"Fiziks",sf::Style::Titlebar);
        window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width - window.getSize().x, sf::VideoMode::getDesktopMode().height - window.getSize().y) / 2);
        window.setFramerateLimit(BackWrapper::FPS);
        while(window.isOpen()) {
            while(window.pollEvent(event)) {
                if((event.type == sf::Event::Closed) || 
                   (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    window.close();
                }

                if(event.type == sf::Event::KeyPressed) {
                    keys[event.key.code] =  true;
                } else {
                    keys[event.key.code] =  false;
                }
            }
            clock.restart().asSeconds() * BackWrapper::FPS;
            window.clear(sf::Color(0x181818FF));
                BackWrapper::render_the_render_list();
            window.display();
        }
        BackWrapper::exit_app = true;
    }    

    void use() {
        BackWrapper::init = SfmlWrapper::init;
        BackWrapper::render = SfmlWrapper::render;
        BackWrapper::render_rect = SfmlWrapper::render_rect;
        BackWrapper::render_point = SfmlWrapper::render_point;
        BackWrapper::key_pressed = SfmlWrapper::key_pressed;
    }    
}


#endif //SFML_WRAPPER_IMPLEMENTATIO
