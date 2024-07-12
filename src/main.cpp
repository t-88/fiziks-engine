#include <stdio.h>
#include <vector>

#include <SFML/Graphics.hpp>


#include "Math.hpp"
#include "Rect.hpp"
#include "World.hpp"


World world;




int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),"Fiziks",sf::Style::Titlebar);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - window.getSize().x) / 2,(sf::VideoMode::getDesktopMode().height - window.getSize().y) / 2));
    

    world.addBody(new Rect(Vec2(100,100),Vec2(50,50)));



    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color(0x181818FF));
        
        for(int i = 0; i < world.bodies.size(); i++) {
            Vec2 size = static_cast<Rect*>(world.bodies[i])->size;
            Vec2 pos = static_cast<Rect*>(world.bodies[i])->pos;

            sf::RectangleShape rect(sf::Vector2f(size.x,size.y));
            rect.setPosition(sf::Vector2f(pos.x,pos.y));
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setFillColor(sf::Color::Transparent);
            
            window.draw(rect);
        }

        window.display();
        
    }

    return 0;
}