#include <sstream>

#include "axis.h"

namespace sf
{
namespace plot
{

Axis::Axis()
{
    if (!font_.loadFromFile("./font.ttf"))
    {
        throw ;
    }

    max_.setFont(font_);
    max_.setCharacterSize(16);
    max_.setColor(sf::Color::Black);
    min_.setFont(font_);
    min_.setCharacterSize(16);
    min_.setColor(sf::Color::Black);
}

void Axis::Compute(float min, float max)
{
    std::stringstream ss;
    ss << min;
    min_.setString(ss.str());

    ss.str(std::string());
    ss << max;
    max_.setString(ss.str());

    min_.setPosition(sf::Vector2f(0, size_.y));
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(min_, states);
    target.draw(max_, states);
}

}
}
