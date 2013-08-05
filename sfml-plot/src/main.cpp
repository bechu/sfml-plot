#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML plot", sf::Style::Default, settings);

    sf::plot::Scene scene(900, 600);

    sf::plot::Curve &curve = scene.CreateCurve("random");

    curve.Plot(0, 0);
    curve.Plot(.1, .5);
    curve.Plot(.2, .3);
    curve.Plot(.3, .3);
    curve.Plot(.35, .8);
    curve.Plot(1, .1);
    //curve.Plot(100);
    //curve.Plot(400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        scene.Build();
        window.draw(scene);
        window.display();
    }

    return 0;
}

