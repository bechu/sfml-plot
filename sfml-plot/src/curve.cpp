#include <cmath>

#include "curve.h"

namespace sf
{
namespace plot
{

Curve::Curve(const Vector2f &size) : size_(size)
{
  setColor(sf::Color(19, 13, 200));
}

void Curve::addValue(double value)
{
  data_.push_back(value);
  if(data_.size() > 100)
  {
    data_.pop_front();
  }
}

void Curve::build(sf::Vector2f &rangex, sf::Vector2f &rangey)
{
  rangex.x = 0;
  rangex.y = data_.size();
  if(data_.size() > 1)
  {
    // calculate the min and max for the inputs value
    for(std::list<double>::iterator it=data_.begin();it!=data_.end();++it)
    {
      if(*it > rangey.y)
        rangey.y = *it;
      if(*it < rangey.x)
        rangey.x = *it;
    }

    line_.clear();
    double distance = fabs(rangey.y-rangey.x);
    if(distance == 0) distance = 1;

    int xoffset = size_.x / (data_.size());

    while(xoffset * data_.size() < (size_.x+xoffset))
      xoffset++;

    int i = 0;
    double x = 0;
    for(std::list<double>::reverse_iterator it=data_.rbegin();it!=data_.rend();++it)
    {
      x = size_.x - (i++ * xoffset);
      double y = size_.y - ((*it-rangey.x) / distance * size_.y);
      if(x < 0)
      {
        // normally with have to calcule the real value of y
        line_.push_back(sf::Vertex(sf::Vector2f(0, y), color_));
        break;
      }
      else
      {
        line_.push_back(sf::Vertex(sf::Vector2f(x, y), color_));
      }
    }
  }
}

void Curve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  std::vector<sf::Vertex> vertices;
  for(std::vector<sf::Vertex>::const_iterator it=line_.begin();it!=line_.end();++it)
  {
    vertices.push_back(sf::Vertex(it->position, fillColor_));
    vertices.push_back(sf::Vertex(sf::Vector2f(it->position.x, size_.y), fillColor_));
  }
  target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip, states);
  target.draw(&line_[0], line_.size(), sf::LinesStrip, states);
}

}
}
