#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "body.h"

#include <iostream>
#include <math.h>
#include <chrono>

//List of bodies
std::vector<Body> bodies;

sf::Font font;

//Create 1 body and add to list of bodies
void spawnBody(float radius, float mass, sf::Vector2f position)
{
    Body body(radius, mass, position);
    bodies.push_back(body);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(3200, 1800), "Gravity");

    font.loadFromFile("./fonts/Sansation_Regular.ttf");

    // Main loop
    while (window.isOpen())
    {
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {

            // Left Click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    spawnBody(50, 50, sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
            }

            // Quit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        //Start clock for timing tests
        std::chrono::steady_clock::time_point beginGravityComp = std::chrono::steady_clock::now();

        // Update each body (calculate velocity for next step), and draw.
        for(int i = 0; i < bodies.size(); i++){
            bodies[i].update(bodies);
            window.draw(bodies[i].getShape());
        }

        std::chrono::steady_clock::time_point endGravityComp = std::chrono::steady_clock::now(); 
        //std::cout << "Gravity computation time = " << std::chrono::duration_cast<std::chrono::microseconds>(endGravityComp - beginGravityComp).count() << "[microseconds]" << std::endl;
        
        //Body counter in top left
        sf::Text atext;
        atext.setFont(font);
        atext.setCharacterSize(100);
        atext.setFillColor(sf::Color::White);
        atext.setPosition(100,50);
        atext.setString(std::to_string(bodies.size()));
        window.draw(atext);
        // end the current frame
        window.display();
    }
    return 0;
}