#ifndef SFML_WRAPPER_HPP
#define SFML_WRAPPER_HPP


#include <SFML/Graphics.hpp>

#include "Math.hpp"
#include "Rect.hpp"

const int FPS = 64;


namespace SfmlWrapper {
    extern sf::RenderWindow window;
    extern sf::Clock clock;
    extern sf::Event event;
    extern float dt;

    void render_rect( Rect rect);
    void render_point(Vec2 pos);
}



#endif //SFML_WRAPPER_HPP

#ifdef SFML_WRAPPER_IMPLEMENTATION

namespace SfmlWrapper {
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Event event;
    float dt;


    void render_rect(Rect r) {
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

    void render_point(Vec2 pos) { 
        sf::CircleShape circle(2);
        circle.setPosition(sf::Vector2f(pos.x - 1,pos.y - 1));
        circle.setFillColor(sf::Color(0xFFA500FF));
        
        window.draw(circle);
    }    
}


#endif //SFML_WRAPPER_IMPLEMENTATIO
