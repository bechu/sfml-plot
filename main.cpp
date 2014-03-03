#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio> // popen
#include <cstring> // memset

#include "src/plot.h"

class Pinger
        : public sf::Drawable
{
public:
    Pinger(const std::string& dns, const sf::Vector2i& location)
        : dns_(dns)
    {
        plot_.setSize(sf::Vector2f(600, 400));
        plot_.setTitle("Ping "+dns);
        plot_.setFont("./font.ttf");
        plot_.setXLabel("Number of ping");
        plot_.setYLabel("milli seconds");
        plot_.setTitleColor(sf::Color::Blue);
        plot_.setBackgroundColor(sf::Color(rand()%255, rand()%255, rand()%255));
        plot_.setTitleColor(sf::Color::Black);
        plot_.setPosition(sf::Vector2f(600*location.x, 400*location.y));
        sf::plot::Curve &curve = plot_.createCurve("ping", sf::Color::Red);
        curve.setFill(rand() % 2);
        curve.setThickness(2 + rand() % 10);
        curve.setColor(sf::Color(rand()%255, rand()%255, rand()%255));
        curve.setLimit(10 + rand() % 100);
    }

    void update()
    {
        sf::plot::Curve &curve = plot_.getCurve("ping");
        curve.addValue(ping(dns_));
        plot_.prepare();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(plot_, states);
    }

    /// launch the ping command and get the ping ms result
    /// not safe !
    /// better in a thread !
    float ping(const std::string& dns)
    {
        std::string cmd = "ping " + dns + " -c 1";
        FILE* file = popen(cmd.c_str(), "r");
        if(!file) return -1.0f;
        char buffer[1024];
        std::memset(buffer, 0, 1024*sizeof(char));
        if(fread(buffer, sizeof(char), 1024, file) == 0)
        {
            pclose(file);
            return -1.0f;
        }
        std::string in(buffer);
        size_t pos = in.find("time=");
        size_t end_pos = in.find(" ms", pos+1);
        if(pos == std::string::npos || end_pos == std::string::npos)
        {
            pclose(file);
            return -1.0f;
        }
        in = in.substr(pos+5, end_pos-(pos+5));
        pclose(file);
        return std::atof(in.c_str());
    }

    sf::plot::Plot plot_;
    std::string dns_;
};


int main()
{
    // initialize the srand
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(600*2, 400*2), "SFML plot", sf::Style::Default);

    sf::Clock clock;
    Pinger google_com("google.com", sf::Vector2i(0, 0));
    Pinger google_fr("google.fr", sf::Vector2i(0, 1));
    Pinger ensta_fr("ensta.fr", sf::Vector2i(1, 0));
    Pinger bechu_org("bechu.org", sf::Vector2i(1, 1));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Each 200 ms, a new random value is add to the random curve
        if(clock.getElapsedTime().asMilliseconds() > 1000)
        {
            clock.restart();
            google_com.update();
            google_fr.update();
            ensta_fr.update();
            bechu_org.update();
        }

        window.clear();

        window.draw(google_com);
        window.draw(google_fr);
        window.draw(ensta_fr);
        window.draw(bechu_org);

        window.display();
    }

    return 0;
}
