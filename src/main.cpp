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

    Rect rect = Rect(Vec2(100,100),Vec2(50,50));
    world.addBody(&rect);
    world.addBody(new  Rect(Vec2(200,200),Vec2(30,30)));


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

#if 0
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            world.bodies[1]->applyForce(Vec2(-5,0));
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            world.bodies[1]->applyForce(Vec2(5,0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            world.bodies[1]->applyForce(Vec2(0,-5));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            world.bodies[1]->applyForce(Vec2(0,5));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { 
            world.bodies[1]->applyTorque(4);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { 
            world.bodies[1]->applyTorque(-4);
        }

#else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            world.bodies[0]->pos.x -= 5;
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            world.bodies[0]->pos.x += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            world.bodies[0]->pos.y -= 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            world.bodies[0]->pos.y += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { 
            world.bodies[0]->rotation += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { 
            world.bodies[0]->rotation -= 5;
        }
#endif
        

        window.clear(sf::Color(0x181818FF));
        world.simulate(dt);


        for(int i = 0; i < world.bodies.size(); i++) {
            Vec2 size = static_cast<Rect*>(world.bodies[i])->size;
            Vec2 pos = world.bodies[i]->pos;
            float rotation = world.bodies[i]->rotation;

            sf::RectangleShape rect(sf::Vector2f(size.x ,size.y));
            rect.setPosition(sf::Vector2f(pos.x,pos.y));
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setOrigin(size.x / 2, size.y / 2 );
            rect.setFillColor(sf::Color::Transparent);
            rect.setRotation(-rotation);


            sf::CircleShape circle(2);
            circle.setPosition(sf::Vector2f(pos.x - 1,pos.y - 1));
            circle.setFillColor(sf::Color(0xFFA500FF));

            std::array<Vec2,4> points = static_cast<Rect*>(world.bodies[i])->getPoints();
            sf::ConvexShape convex;
            convex.setPointCount(4);
            for(int i = 0; i < 4; i++) {
                convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
            }
            convex.setFillColor(sf::Color::Red);

            
            window.draw(rect);
            window.draw(circle);
            // window.draw(convex);
        }

        window.display();
        
    }

    return 0;
}