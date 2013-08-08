#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "src/plot.h"

int main()
{
  srand (time(NULL));

  // Create the sfml window
  sf::RenderWindow window(sf::VideoMode(400, 400), "SFML plot", sf::Style::Default);

  // Create a new plot with the size and the title
  sf::plot::Plot plot(sf::Vector2f(400, 400), "test1");

  // Specify the font to use (be sure that you have the file in the good place)
  plot.setFont("./font.ttf");

  // Fill label for each axis
  plot.setXLabel("Number of data");
  plot.setYLabel("Random values");

  // Create a curve with a name
  sf::plot::Curve &curve = plot.createCurve("random");

  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // Rach 200 ms, a new random value is add to the random curve
    if(clock.getElapsedTime().asMilliseconds() > 200)
    {
      curve.addValue(rand() % 20 - 10);
      clock.restart();
    }

    window.clear();

    // Build everything needed for the rendering part
    plot.build();

    // Draw the plot
    window.draw(plot);

    window.display();
  }

  return 0;
}
