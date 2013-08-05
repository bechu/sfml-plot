#include <iostream>
#include "curve.h"

namespace sf
{
namespace plot
{

Curve::Curve(const sf::Vector2i &size) : size_(size)
{

}

void Curve::Plot(float x, float y)
{
    line_.push_back(sf::Vertex(sf::Vector2f(x*size_.x, y*size_.y), sf::Color(200, 0, 0)));
}

void Curve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    std::vector<sf::Vertex> vertices;
    for(std::vector<sf::Vertex>::const_iterator it=line_.begin();it!=line_.end();++it)
    {
        vertices.push_back(sf::Vertex(it->position, sf::Color(200, 200, 0, 100)));
        vertices.push_back(sf::Vertex(sf::Vector2f(it->position.x, size_.y), sf::Color(200, 200, 0, 100)));
    }
    //vertices.push_back(sf::Vertex(sf::Vector2f(0, size_.y), sf::Color(200, 200, 0)));
    //vertices.push_back(sf::Vertex(sf::Vector2f(size_.x, size_.y), sf::Color(200, 200, 0)));
    target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip, states);

    target.draw(&line_[0], line_.size(), sf::LinesStrip, states);
    //for(std::vector<sf::Vertex>::const_iterator it=line_.begin();it!=line_.end();++it)
    //{
    //    sf::CircleShape shape(50);
    //    shape.setFillColor(sf::Color(100, 250, 50));
    //    shape.setPosition(it->position);
    //    target.draw(shape);
    //}
}

}
}
