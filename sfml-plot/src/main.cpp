#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "scene.h"

int main()
{
    srand (time(NULL));

    // Create the sfml window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML plot", sf::Style::Default);

    // Create a new scene and change the position
    sf::plot::Scene scene(400*1.1, 400*1.1);
    scene.setPosition(100, 100);

    // Create a new curve call random
    sf::plot::Curve &curve = scene.CreateCurve("random");

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // each 200 ms, a new random value is add
        if(clock.getElapsedTime().asMilliseconds() > 200)
        {
            curve.Plot(rand() % 20 + 1-10);
            clock.restart();
        }

        window.clear();

        // Build the scene
        scene.Build();
        // Draw the scene
        window.draw(scene);

        window.display();
    }

    return 0;
}
