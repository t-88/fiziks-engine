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
    window.setFramerateLimit(60);
    sf::Clock clock;
    float dt = 0;

    Rect rect = Rect(Vec2(100,100),Vec2(5,5));
    world.addBody(&rect);


    while(window.isOpen()) {
        sf::Event event;
        dt = clock.restart().asSeconds() * 60;
        
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rect.applyForce(Vec2(-10,0));
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rect.applyForce(Vec2(10,0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
            rect.applyTorque(20);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { 
            rect.applyTorque(-20);
        }

        

        window.clear(sf::Color(0x181818FF));
        world.simulate(dt);


        for(int i = 0; i < world.bodies.size(); i++) {
            Vec2 size = static_cast<Rect*>(world.bodies[i])->size;
            Vec2 pos = world.bodies[i]->pos;
            float rotation = world.bodies[i]->rotation;

            sf::RectangleShape rect(sf::Vector2f(size.x * 10,size.y  * 10));
            rect.setPosition(sf::Vector2f(pos.x,pos.y));
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setOrigin(size.x * 10/ 2, size.y * 10 / 2);
            rect.setFillColor(sf::Color::Transparent);
            rect.setRotation(-rotation);


            sf::CircleShape circle(2);
            circle.setPosition(sf::Vector2f(pos.x - 1,pos.y - 1));
            circle.setFillColor(sf::Color(0xFFA500FF));
            
            window.draw(rect);
            window.draw(circle);
        }

        window.display();
        
    }

    return 0;
}